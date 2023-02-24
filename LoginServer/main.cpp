#include "BaseInc.h"
#include "LoginServer.h"
#include "SendEmail.h"
GS g;
LoginServer server;
int main()
{
	//stringstream ss;
	//ss << "123 233\r\n";
	//ss << "223 acc\r\n";
	//ss << "323 dda\r\n";
	//ss << "423 23a\r\n";
	//ss << "523 gf\r\n";
	//ss << "623 z";
	//string str;

	//ss >> str;
	//char ch[1024];
	//int size = 1024;
	//while (!ss.eof())
	//{
	//	ss.getline(ch, size);
	//	str = ch;
	//	char ch = str.back();
	//	if (ch != '\r')
	//	{

	//	}
	//}
	cout << "服务器初始化中..." << endl;
	::Sleep(200);
	cout << "服务器初始化完成" << endl;
	cout << "监听"<< 32651 << endl;
	server.StartServer();
	cout << "服务器监听..."<< 32651 << endl;
	server.RecvMessageFunc();
	
	return 0;
}
