#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <thread> //�־û�ʱ��ʹ���߳�
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <sstream>

#include <algorithm>
#include "./include/tools.h"
#include "./include/CmdHandler.h"

// �߳�ͬ�����õ��Ķ���
std::mutex mtx;
std::condition_variable cond;
std::unordered_map<std::string, std::string> data_map;

// �����,������������.
std::unordered_set<std::string> cmd_set;

int main(int argc, char* argv[])
{
	CmdHandler cmd_handler;
	std::cout << "		Wellcome to MyRedis.If you are first time use MyRedis, you can enter <help> ." << std::endl;
	cmd_handler.handleloop();
	return 0;
}