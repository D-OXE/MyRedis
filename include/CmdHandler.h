#pragma
#include <string>
#include <vector>
#include <thread>
#include <unordered_set>

//����cmd ��һ����
class CmdHandler
{
public:
	//��������ѭ��,ÿ����������,���¼��Ч���������Cmd_Cache��
	void handleloop();

	//�����������Ҫ�����ļ���ر�RDB/AOF�ļ�
	CmdHandler();
	~CmdHandler();

private:
	void handle_cmd(const std::string &cmd);
	void set_key();
	bool get_key(const std::string &key, std::string &value);
	bool del_key(const std::string &key);

	bool scan_var();

	void SaveRDB();		// �����ݱ��浽RDB�ļ���,�ļ�·���Ժ�����
	void LoadRDB();		// ��ȡRDB�ļ�,�ļ�·���Ժ�����

	void SaveAOF();		// �����ݱ��浽AOF�ļ���,�ļ�·���Ժ�����
	void LoadAOF();		// ��ȡAOF�ļ�,�ļ�·���Ժ�����

	//����������,����׷�ӵ�AOF�ļ���
	std::vector<std::vector<std::string>> Cmd_Cache;
	std::vector<std::vector<std::string>> Cmd_Cache_Save;

	// ר���ڻ���������߳�
	std::thread save_thread;
	std::unordered_set<std::string> SupportedCmd; // ֧�ֵ�����

	
};