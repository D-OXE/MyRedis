#include "../include/CmdHandler.h"
#include "../include/tools.h"
#include <string>
#include <iostream>
#include <sstream>

CmdHandler::CmdHandler()
{
	// 构造
	this->SupportedCmd = {"set", "get", "save", "exit", "del", "scan", "help"};
}

CmdHandler::~CmdHandler()
{
	// 析构
}

void CmdHandler::handle_cmd(const std::string &cmd)
{
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
	}else if (*it == "exit" || *it == "e" || *it == "quit" || *it == "q")
	{
		std::cout << " thank you for your using. Bye " << std::endl;
		// 这里可以追加线程同步语句,将flag修改为不执行 eventloop,等待所有线程执行完毕,再退出程序
	}
	else if (*it == "set")
	{
		// string 的set命令
		this->set_key(); // 可以添加线程同步方面的东西.Cmd_Cache
		std::cout << "test set" << std::endl;
	}
	else if (*it == "scan")
	{
		std::cout << "test scan" << std::endl;
	}
	else if (*it == "save")
	{
		std::cout << "test save" << std::endl;
		// 启动保存线程 ,保存AOF和RDB文件.这里是不是可以细分?
	}
	else if (*it == "get")
	{
		std::cout << "test get" << std::endl;
	}
}
// 事件循环,将输入格式化,交由 handle_cmd处理
void CmdHandler::handleloop()
{
	std::string input, lowerinput;

	std::vector<std::string> cmd_list;
	int cmd_num = 0;

	// int type;
	while (true) // 这里需要修改为同步flag判断循环是否继续执行
	{
		// 完成输入,然后抛出任务给其他函数或者线程完成.
		std::cout << "->>";
		std::getline(std::cin, input);
		lowerinput = toLowerCase(input);

		std::istringstream strin(input);
		// std::istringstream strsave(input); // 用于缓存命令的字符串流 ,这里后续可以优化


		while (strin)
		{
			strin >> cmd_list[cmd_num++];
		}

		// 判断输入命令,并检验合法性,将输入命令打包放在Cmd_Cache中,启动缓存线程任务

		this->handle_cmd(cmd_list[0]);
	}
}