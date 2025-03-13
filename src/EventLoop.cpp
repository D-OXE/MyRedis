#include "../include/CmdHandler.h"
#include "../include/tools.h"
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

CmdHandler::CmdHandler():Running(true)
{
	// 构造
	this->SupportedCmd = {
		"set",
		"get",
		"save",
		"del",
		"help",
		"scan",

		"expire",  // 设置过期时间
		"ttl",	   // 查看过期时间
		"persist", // 取消过期时间

		"quit", // 退出命令
		"q",
		"exit",
		"e",
	};

	// 启动删除过期时间键的线程
	this->delete_timeout = std::move(std::thread(&CmdHandler::check_ttl_key, this));

}

CmdHandler::~CmdHandler()
{
	// 析构
	{
		std::unique_lock<std::mutex> lock(mtx);
		Running = false; // 通知线程退出循环
	}
	if (delete_timeout.joinable())
	{
		delete_timeout.join(); // 等待线程结束
	}

}

void CmdHandler::handle_cmd()
{
	/*
	本函数的优化方法:
	1. 使用命令映射表（Command Map）
	将命令与其对应的处理函数绑定到一个映射表中（如 std::unordered_map），通过查找映射表直接调用对应的处理函数。

	*/
	// 线程同步
	std::string cmd = cmd_list[0]; // 此时已经被转换为小写
	time_t now = std::time(nullptr);

	auto it = this->SupportedCmd.find(cmd);

	if (it == this->SupportedCmd.end())
	{
		// 没有这个命令,查找失败
		std::cout << "Error cmd input :" << cmd << ", input again." << std::endl;
		return;
	}

	if (*it == "help")
	{
		std::cout << "test help" << std::endl;
	}
	else if (*it == "exit" || *it == "e" || *it == "quit" || *it == "q")
	{
		// 修改为专门的退出函数,妥善处理线程安全问题.......
		this->quit();
	}
	else if (*it == "set")
	{
		this->set_key();
	}
	else if (*it == "scan")
	{
		this->scan_var();
	}
	else if (*it == "save")
	{
		this->SaveRDB();	//没有必要单起线程,直接顺序执行即可
	}
	else if (*it == "get")
	{
		this->get_key();
	}
	else if (*it == "del")
	{
		this->del_key();
	}
	else if (*it == "expire")
	{
		this->expire(1); // TODO string 类型设置为 1如何判断输入的类型?
	}
	else if (*it == "ttl")
	{
		this->ttl();
	}
	else if (*it == "persist")
	{
		this->persist();
	}
}
// 事件循环,将输入格式化,交由 handle_cmd处理
void CmdHandler::handleloop()
{
	std::string input, lowerinput;

	int cmd_num = 0;

	// int type;
	while (Running) // 这里需要修改为同步flag判断循环是否继续执行
	{
		// 完成输入,然后抛出任务给其他函数或者线程完成.
		std::cout << "->>";
		std::getline(std::cin, input);
		if (input.empty()) // 检查是否为空行
		{
			continue; // 跳过空行
		}

		std::istringstream strin(input);

		// std::istringstream strsave(input); // 用于缓存命令的字符串流 ,这里后续可以优化

		while (strin) // 拆分命令,存入缓存命令列表中
		{
			std::string temp;
			strin >> temp;
			if (temp != "")
			{
				cmd_list.push_back(temp);
				cmd_num++;
			}
		}

		// 判断输入命令,并检验合法性,将输入命令打包放在Cmd_Cache中,启动缓存线程任务
		lowerinput = toLowerCase(cmd_list[0]); // TODO:仅将输入命令转换为小写,键值对不转换.后续遇到组合命令,可能需要转换.

		// 单次循环处理单次输入的命令
		this->handle_cmd();
		cmd_list.clear();
	}
}