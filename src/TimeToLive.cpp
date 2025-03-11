#include "../include/CmdHandler.h"
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

void CmdHandler::expire(int type)
{
	// 线程同步
	std::time_t now = std::time(nullptr);
	time_t max_time = std::numeric_limits<time_t>::max();

	if (cmd_list.size() != 3)
	{
		std::cout << "Error cmd input : plase enter as:\n	expire Key <unsigned int>" << std::endl;
		return;
	}
	else if (std::stoi(cmd_list[2]) < 0)
	{
		std::cout << "Error cmd input : plase enter as:\n	expire Key <unsigned int>" << std::endl;
		return;
	}
	auto it = DataStringKV.find(cmd_list[1]);
	if (it == DataStringKV.end())
	{
		std::cout << "Error cmd input : Key not found" << std::endl;
	}
	else
	{
		// 设置Unix时间戳
		it->second.first = now + static_cast<time_t>(std::stoi(cmd_list[2]));
	}
}
void CmdHandler::ttl()
{
	// 线程同步
	if (cmd_list.size() != 2)
	{
		std::cout << "Error cmd input : plase enter as:\n	ttl Key" << std::endl;
		return;
	}
	else
	{
		auto it = DataStringKV.find(cmd_list[1]);
		if (it == DataStringKV.end())
		{
			std::cout << "Error cmd input : Key not found" << std::endl;
			return;
		}
		std::cout << it->second.first << std::endl;
	}
}
void CmdHandler::persist()
{
	if (cmd_list.size() != 2)
	{
		std::cout << "Error cmd input : plase enter as:\n	persist Key" << std::endl;
		return;
	}
	else
	{
		time_t max_time = std::numeric_limits<time_t>::max();
		auto it = DataStringKV.find(cmd_list[1]);
		if (it == DataStringKV.end())
		{
			std::cout << "Error cmd input : Key not found" << std::endl;
			return;
		}
		it->second.first = max_time;
	}
}

// 删除过期的键,定期删除机制,而不是惰性删除.单独一个线程.每10秒执行一次这个任务,构造中启动
void CmdHandler::check_ttl_key()
{
	while (Running)
	{ // 由 Running 标志控制循环
		std::this_thread::sleep_for(std::chrono::seconds(5));

		std::lock_guard<std::mutex> lock(mtx); // 确保线程安全
		auto now = std::time(nullptr);

		for (auto it = DataStringKV.begin(); it != DataStringKV.end();)
		{
			if (it->second.first < now)
			{
				it = DataStringKV.erase(it); // erase 返回下一个有效迭代器
			}
			else
			{
				++it;
			}
		}
	}
}