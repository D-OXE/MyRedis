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
	// 对于save命令.后续可以增加set ,或者map命令头在第一行,用于读取数据时,将对应数据放进对应的结构体中.
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
			//set 命令用于普通键值对
			rdb << "set " << i.first << " " << i.second.second << std::endl;
		}
		rdb.close();
	}
}