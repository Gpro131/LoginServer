#pragma once
#include "BaseInc.h"
#include "TcpServer.h"

class LoginServer
{
public:
	LoginServer();
	~LoginServer();

	void StartServer();
	void RecvMessageFunc();

	void RecvMsg(SOCKET s,char* data,int count);
private:
	void OnRecvMsg(std::string,SOCKET s,char* buff,int count);
	void OnInit();
	void UpdateData();
	void SendEmail(string recEmail,string sendEmail,string sendPwd,string content);

	TcpServer tcpServer;
	deque<char> dqRecvsChars;
	std::map<string, string> mpClient;

};