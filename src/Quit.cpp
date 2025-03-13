#include "../include/CmdHandler.h"
#include <fstream>
#include <iostream>
#include <string>
#include <mutex>
#include <memory>
#include <unordered_map>


void CmdHandler::quit()
{
	std::unique_lock<std::mutex> lock(mtx);
	Running = false;
	std::cout << " thank you for your using. Bye " << std::endl;
}