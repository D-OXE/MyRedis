#include "../include/CmdHandler.h"
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <mutex>
#include <memory>
#include <condition_variable>

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
	{
		// 线程同步
		std::unique_lock<std::mutex> lock(mtx);
		auto it = DataStringKV.find(cmd_list[1]);
		if (it == DataStringKV.end())
		{
			std::cout << "Error cmd input : Key not found" << std::endl;
		}
		else
		{
			// 设置Unix时间戳,可以增加线程同步限制
			it->second.first = now + static_cast<time_t>(std::stoi(cmd_list[2]));
		}
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
		std::unique_lock<std::mutex> lock(mtx);
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
		std::unique_lock<std::mutex> lock(mtx);
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
		std::this_thread::sleep_for(std::chrono::seconds(30));
		auto now = std::time(nullptr);
		{
			std::unique_lock<std::mutex> lock(mtx); // 确保线程安全
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
}