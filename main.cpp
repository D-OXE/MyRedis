#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <thread> //持久化时候使用线程
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <sstream>

#include <algorithm>
#include "./include/tools.h"
#include "./include/CmdHandler.h"

// 线程同步会用到的东西
std::mutex mtx;
std::condition_variable cond;
std::unordered_map<std::string, std::string> data_map;

// 命令集合,后续会逐渐增加.
std::unordered_set<std::string> cmd_set;

int main(int argc, char *argv[])
{
	CmdHandler cmd_handler;
	std::cout << "		Wellcome to MyRedis.If you are first time use MyRedis, you can enter <help> ." << std::endl;
	cmd_handler.handleloop();
	return 0;
}