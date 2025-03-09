#include "../include/CmdHandler.h"
#include "../include/tools.h"
#include <string>
#include <iostream>
#include <sstream>

CmdHandler::CmdHandler()
{
	// ����
	this->SupportedCmd = {"set", "get", "save", "exit", "del", "scan", "help"};
}

CmdHandler::~CmdHandler()
{
	// ����
}

void CmdHandler::handle_cmd(const std::string &cmd)
{
	auto it = this->SupportedCmd.find(cmd);
	if (it == this->SupportedCmd.end())
	{
		// û���������,����ʧ��
		std::cout << "Error cmd input :" << cmd << ", input again." << std::endl;
		return;
	}

	if (*it == "help")
	{
		std::cout << "test help" << std::endl;
	}else if (*it == "exit" || *it == "e" || *it == "quit" || *it == "q")
	{
		std::cout << " thank you for your using. Bye " << std::endl;
		// �������׷���߳�ͬ�����,��flag�޸�Ϊ��ִ�� eventloop,�ȴ������߳�ִ�����,���˳�����
	}
	else if (*it == "set")
	{
		// string ��set����
		this->set_key(); // ��������߳�ͬ������Ķ���.Cmd_Cache
		std::cout << "test set" << std::endl;
	}
	else if (*it == "scan")
	{
		std::cout << "test scan" << std::endl;
	}
	else if (*it == "save")
	{
		std::cout << "test save" << std::endl;
		// ���������߳� ,����AOF��RDB�ļ�.�����ǲ��ǿ���ϸ��?
	}
	else if (*it == "get")
	{
		std::cout << "test get" << std::endl;
	}
}
// �¼�ѭ��,�������ʽ��,���� handle_cmd����
void CmdHandler::handleloop()
{
	std::string input, lowerinput;

	std::vector<std::string> cmd_list;
	int cmd_num = 0;

	// int type;
	while (true) // ������Ҫ�޸�Ϊͬ��flag�ж�ѭ���Ƿ����ִ��
	{
		// �������,Ȼ���׳�������������������߳����.
		std::cout << "->>";
		std::getline(std::cin, input);
		lowerinput = toLowerCase(input);

		std::istringstream strin(input);
		// std::istringstream strsave(input); // ���ڻ���������ַ����� ,������������Ż�


		while (strin)
		{
			strin >> cmd_list[cmd_num++];
		}

		// �ж���������,������Ϸ���,����������������Cmd_Cache��,���������߳�����

		this->handle_cmd(cmd_list[0]);
	}
}