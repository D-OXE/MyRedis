#include "../include/CmdHandler.h"
#include <fstream>
#include <iostream>
#include <string>
#include <mutex>
#include <memory>
#include <unordered_map>

const char *RDBPATH = "./data/rdb.dat";
void CmdHandler::SaveRDB()
{
	std::ofstream rdb(RDBPATH, std::ios::app);
	if (!rdb.is_open())
	{
		std::cerr << " Failed to open :" << RDBPATH << std::endl;
		return;
	}
	{
		std::unique_lock<std::mutex> lock(mtx);
		if (!Running)
		{
			// 如果 Running 为 false，直接退出函数
			rdb.close();
			return;
		}
		for (auto &i : DataStringKV)
		{
			rdb << i.first << " " << i.second.second << std::endl;
		}
		rdb.close();
	}
}