#include "BaseInc.h"
#include "Account.h"
#include <iosfwd>
#include <utility>
#include <fstream>

using namespace std;
AccountSystem::AccountSystem()
{
}
AccountSystem::~AccountSystem()
{
	
}
bool AccountSystem::Login(std::string usr, std::string pwd) {
	if (usr.empty() || pwd.empty())
	{
		return false;
	}
	if (mpAccount.find(usr) == mpAccount.end())
	{
		return false;
	}
	if (mpAccount[usr] == pwd)
	{
		return true;
	}

	return false;
}
bool AccountSystem::Register(std::string usr, std::string pwd) {
	if (usr.empty() || pwd.empty())
	{
		return false;
	}
	if (mpAccount.find(usr) == mpAccount.end())
	{
		mpAccount[usr] = pwd;
		return true;
	}
	return false;
}
void AccountSystem::OnInit()
{
	ifs.open("account.data");
	if (!ifs.is_open())
	{
		return;
	}

	char ch[2048];
	string usr;
	string pwd;
	stringstream ss;
	char buff[2048];
	while (!ifs.eof())
	{
		memset(ch, 0, 2048);
		ifs.getline(ch, 2048);
		ss.clear();
		ss.seekg(0);
		ss.seekp(0);
		ss.str(string(ch));
		ss >> usr;
		ss >> pwd;
		if (mpAccount.find(usr) == mpAccount.end())
			mpAccount[usr] = pwd;
	}
	ifs.close();
}
void AccountSystem::SaveFile()
{
	std::ofstream ofs;
	ofs.open("account.data");
	if (!ofs.is_open())
	{
		return;
	}
	char ch[2048];
	string usr, pwd;
	for (auto p : mpAccount)
	{
		ofs<<p.first.data()<<" ";
		ofs<<p.second<<endl;
		//memset(ch, 0, 2048);
		//getline(ofs,ch,2048);
		//stringstream ss(ch);

		//if(mpAccount.find(usr) == mpAccount.end())
		//	mpAccount[usr] = pwd;
	}
	ofs.flush();
	ofs.close();
}