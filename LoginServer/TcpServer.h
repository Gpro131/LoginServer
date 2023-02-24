#pragma once
#include "BaseInc.h"
class TcpServer {
public:
	~TcpServer() { isRecvThreadRunnning = false; }
	void Init(int port);
	void StartRecvThread(bool isAsync);
	std::function<void(string, SOCKET, char*, int)> RecvHandler;
	bool GetIsRunning() { return isRecvThreadRunnning; }
	void Close() {
		closesocket(serverSock);
		isRecvThreadRunnning = false;
	}
	void Send(char* buff, int size);
	void ClientOffline(SOCKET s);
	std::string name;
	std::vector<SOCKET> clientList;
private:
	void RecvThread();
	SOCKET AcceptClient();
	SOCKET serverSock;
	volatile	bool isRecvThreadRunnning{ false };

};