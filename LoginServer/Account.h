#pragma once
#include <string>
#include <map>
class AccountSystem
{
public:
	static AccountSystem& GetInst() {
		static AccountSystem inst;
		return inst;
	}

	bool Login(std::string usr, std::string pwd);
	bool Register(std::string usr,std::string pwd);
	void OnInit();
	void SaveFile();
	AccountSystem();
	~AccountSystem();
private:
	std::ifstream ifs;
	std::map<std::string, std::string> mpAccount;
};