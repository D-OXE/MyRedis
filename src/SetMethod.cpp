#include "../include/CmdHandler.h"
#include <string>
#include <iostream>
void CmdHandler::scan_var()
{
	// 线程同步
	for (auto it = DataStringKV.begin(); it != DataStringKV.end(); ++it)
	{
		std::cout << it->first << " " << it->second.second << std::endl;
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
	time_t max_time = std::numeric_limits<time_t>::max();
	DataStringKV[cmd_list[1]].second = cmd_list[2];
	DataStringKV[cmd_list[1]].first = max_time;			// long能表示最大的Unix时间戳
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
		std::cout << it->second.second << std::endl;
	}
}

void CmdHandler::del_key()
{
	// 线程
	if (cmd_list.size() != 2)
	{
		std::cout << "Error cmd input : plase enter as:\n	del Key" << std::endl;
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
		DataStringKV.erase(it);
	}
}

