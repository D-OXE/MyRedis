#pragma
#include <string>
#include <vector>
#include <thread>
#include <unordered_set>
#include <unordered_map>

// 处理cmd 的一个类
class CmdHandler
{
public:
	// 命令输入循环,每次输入命令,会记录有效命令参数到Cmd_Cache中
	void handleloop();

	// 构造和析构中要加载文件或关闭RDB/AOF文件
	CmdHandler();
	~CmdHandler();

private:
	bool Running = true;

	void handle_cmd();
	void set_key();
	void get_key();
	void del_key();

	void scan_var();

	void SaveRDB(); // 将数据保存到RDB文件中,文件路径稍后配置
	void LoadRDB(); // 读取RDB文件,文件路径稍后配置

	void SaveAOF(); // 将数据保存到AOF文件中,文件路径稍后配置
	void LoadAOF(); // 读取AOF文件,文件路径稍后配置

	// 输入的命令缓存,用于追加到AOF文件中
	std::vector<std::vector<std::string>> Cmd_Cache;
	std::vector<std::vector<std::string>> Cmd_Cache_Save;

	// 专用于缓存命令的线程
	std::thread save_thread;
	std::unordered_set<std::string> SupportedCmd; // 支持的命令

	// 一次输入的命令
	std::vector<std::string> cmd_list;

	// 用于存储键值对的结构
	std::unordered_map<std::string, std::string> DataStringKV;
};