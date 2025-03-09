#include "../include/CmdHandler.h"
#include "../include/tools.h"
#include <string>
#include <iostream>
#include <sstream>

CmdHandler::CmdHandler()
{
	// 构造
	this->SupportedCmd = {
		"set",
		"get",
		"save",
		"del",
		"scan",
		"help",

		"quit", // 退出命令
		"q",
		"exit",
		"e",
	};
}

CmdHandler::~CmdHandler()
{
	// 析构
}

void CmdHandler::scan_var()
{
	// 线程同步
	for (auto it = DataStringKV.begin(); it != DataStringKV.end(); ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
}

void CmdHandler::set_key()
{
	// 添加线程同步
	if (cmd_list.size() != 3)
	{
		std::cout << "Error cmd input : plase enter as:\n	set Key Value" << std::endl;
		return;
	}
	DataStringKV[cmd_list[1]] = cmd_list[2];
}

void CmdHandler::get_key()
{
	// 线程
	if (cmd_list.size() != 2)
	{
		std::cout << "Error cmd input : plase enter as:\n	get Key" << std::endl;
		return;
	}
	auto it = DataStringKV.find(cmd_list[1]);
	if (it == DataStringKV.end())
	{
		std::cout << "There is no corresponding key, please check your input key" << std::endl;
		return;
	}
	else
	{
		std::cout << it->second << std::endl;
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
	std::string cmd = cmd_list[0];

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
		Running = false;
		std::cout << " thank you for your using. Bye " << std::endl;
		// 这里可以追加线程同步语句,将flag修改为不执行 eventloop,等待所有线程执行完毕,再退出程序
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
		std::cout << "test save" << std::endl;
		// 启动保存线程 ,保存AOF和RDB文件.这里是不是可以细分?
	}
	else if (*it == "get")
	{
		this->get_key();
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
		lowerinput = toLowerCase(input);

		std::istringstream strin(lowerinput);
		// std::istringstream strsave(input); // 用于缓存命令的字符串流 ,这里后续可以优化

		while (strin)
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

		this->handle_cmd();
		cmd_list.clear();
	}
}