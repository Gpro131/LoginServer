#include "TcpServer.h"
#include "LoginServer.h" 
#include "Account.h"
#include "tool.h"
#include <string>
#include "SendEmail.h"
#include <math.h>
LoginServer::LoginServer()
{

}

LoginServer::~LoginServer()
{
	UpdateData();
}

void LoginServer::StartServer()
{
	tcpServer.Init(32651);
	OnInit();
	tcpServer.RecvHandler = std::bind(&LoginServer::OnRecvMsg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
}

void LoginServer::RecvMessageFunc()
{
	tcpServer.StartRecvThread(false);
}

void LoginServer::RecvMsg(SOCKET s, char* data, int count)
{
	//wchar_t* wd = (wchar_t*)data;
	//std::string utf8Msg = data; 
	//std::wstring unicodeMsg = Utf82Unicode(utf8Msg);
	//const char* chData = utf8Msg.data();
	std::string ssmsg = data;// WChars2Chars(CP_UTF8, std::wstring(wd));
	/*UnicodeToAscii(const_cast<wchar_t*>((wchar_t*)chData));*/
	//std::wstring msg = data;/ Chars2WChars(CP_UTF8, ssmsg);
	/*UnicodeToAscii(const_cast<wchar_t*>((wchar_t*)chData));*/
	//char* ch = new char[count];
	//wchars2chars(wd, data, count);
	string str = ssmsg;
	//cout << msg << endl;
	stringstream ss(str);
	string cmd, args0, args1;
	ss >> cmd;
	string responseStr;

	if (cmd == "Login")
	{
		ss >> args0;
		ss >> args1;
		cout << args0 << " " << args1 << endl;
		bool result = AccountSystem::GetInst().Login(args0, args1);
		if (result)
		{
			responseStr = "LoginSuccess";
		}
		else
		{
			responseStr = "LoginFail";
		}
		send(s, responseStr.data(), responseStr.size(), 0);
	}
	if (cmd == "Register")
	{
		ss >> args0;
		ss >> args1;
		cout << args0 << " " << args1 << endl;
		bool result = AccountSystem::GetInst().Register(args0, args1);
		if (result)
		{
			responseStr = "RegisterSuccess";
		}
		else
		{
			responseStr = "RegisterFail";
		}
		send(s, responseStr.data(), responseStr.size(), 0);
		UpdateData();
	}
	if (cmd == "EmailLoginSend")
	{
		ss >> args0;
		char chTemp[6];
		for (int i = 0;i < 6;i++)
		{
			char ch = rand() % 255;
			chTemp[i] = ch;
		}
		mpClient[args0] = chTemp;
		string content = std::string("本次登录的验证码为:") + mpClient[args0];
		SendEmail(args0, "yang1316973175@163.com", "YHZZHVXMVNMTSGSS", content);
		responseStr = "EmailLoginSendSuccess";
	}
	if (cmd == "EmailLoginVerify")
	{
		ss >> args0 >> args1;
		auto findIter = mpClient.find(args0);
		if (findIter != mpClient.end())
		{
			if (mpClient[args0] == args1)
			{
				responseStr = "LoginSuccess";
			}
			else {
				responseStr = "LoginFailed";
			}
			mpClient.erase(findIter);
		}else
			responseStr = "EmailLoginCancle";
	}
	send(s, responseStr.data(), responseStr.size(), 0);
}

void LoginServer::OnRecvMsg(std::string mode, SOCKET s, char* buff, int count)
{
	for (int i = 0;i < count;i++)
	{
		if (buff[i] != 0 && buff[i] != '\n')
		{
			dqRecvsChars.push_back(buff[i]);
		}
		else {
			if (buff[i] == '\n')
			{
				dqRecvsChars.push_back(buff[i]);
				vector<char> vctData;
				while (dqRecvsChars.size() > 0)
				{
					vctData.push_back(dqRecvsChars.front());
					dqRecvsChars.pop_front();
				}

				RecvMsg(s, vctData.data(), vctData.size());
				dqRecvsChars.clear();
				dqRecvsChars.shrink_to_fit();
			}
		}
	}
}

void LoginServer::OnInit()
{
	AccountSystem::GetInst().OnInit();
}

void LoginServer::UpdateData()
{
	AccountSystem::GetInst().SaveFile();
}

void LoginServer::SendEmail(string recEmail, string sendEmail, string sendPwd, string content)
{
	//sMailInfo mailInfo;
	//mailInfo.mailbox_sender = const_cast<char*>(sendEmail.data());
	//mailInfo.mailbox_receiver = const_cast<char*>(recEmail.data());
	//mailInfo.mail_title = "email login";
	//mailInfo.mailbox_sender_show_name = "send show name";
	//mailInfo.mailbox_user_name = const_cast<char*>(sendPwd.data());
	//mailInfo.mailbox_user_pwd = const_cast<char*>(sendPwd.data());
	////mailInfo.mail_server_ip_addr = "smtp.163.com";

	//memset(mailInfo.mail_server_ip_addr, 0, 32);
	//strcpy(mailInfo.mail_server_ip_addr, "smtp.163.com");

	//memset(mailInfo.mail_body, 0, 32);
	//strcpy(mailInfo.mail_body, content.data());

	//CSendMail csMail;
	//csMail.BeginSendMail(mailInfo);

	//string sendEmail = "yang1316973175@163.com";
	//string recEmail = "1316973175@qq.com";
	//string sendPwd = "YHZZHVXMVNMTSGSS";
	//string content = "hello content";

	sMailInfo mailInfo;
	mailInfo.mailbox_sender = const_cast<char*>(sendEmail.data());
	mailInfo.mailbox_receiver = const_cast<char*>(recEmail.data());
	mailInfo.mail_title = "email login";
	mailInfo.mailbox_sender_show_name = "send show name";
	mailInfo.mailbox_user_name = const_cast<char*>(sendEmail.data());
	mailInfo.mailbox_user_pwd = const_cast<char*>(sendPwd.data());
	//mailInfo.mail_server_ip_addr = "smtp.163.com";

	mailInfo.mail_server_name = "smtp.163.com";
	//memset(mailInfo.mail_server_name, 0, 32);
	//strcpy(mailInfo.mail_server_name, "smtp.163.com");

	/*memset(mailInfo.mail_body, 0, 32);
	strcpy(mailInfo.mail_body, content.data());*/
	mailInfo.mail_body = const_cast<char*>(content.data());

	CSendMail csMail;
	csMail.BeginSendMail(mailInfo);


}

