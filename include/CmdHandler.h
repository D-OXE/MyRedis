#pragma
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_set>
#include <unordered_map>
#include <atomic>

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
	void handle_cmd(); // 处理命令
	void set_key();	   // ok
	void get_key();	   // ok
	void del_key();	   // ok

	void scan_var(); // ok

	void expire(int type); // 设置过期时间
	void ttl();			   // 查看过期时间
	void persist();		   // 取消过期时间

	void check_ttl_key(); // 删除过期键值对,int表示删除哪种类型的键值

	void quit();	// TODO 这个函数将来需要用于优化推出命令,要适配线程同步
	void SaveRDB(); // 将数据保存到RDB文件中,文件路径稍后配置
	void LoadRDB(); // 读取RDB文件,文件路径稍后配置

	void SaveAOF(); // 将数据保存到AOF文件中,文件路径稍后配置
	void LoadAOF(); // 读取AOF文件,文件路径稍后配置

	bool Running;
	std::mutex mtx;

		// 输入的命令缓存,用于追加到AOF文件中
	std::vector<std::vector<std::string>> Cmd_Cache;
	std::vector<std::vector<std::string>> Cmd_Cache_Save;

	std::unordered_set<std::string> SupportedCmd; // 支持的命令
	
	// 一次输入的命令
	std::vector<std::string> cmd_list;
	
	// 用于存储键值对的结构
	std::unordered_map<std::string, std::pair<time_t, std::string>> DataStringKV;
	std::thread delete_timeout;
};