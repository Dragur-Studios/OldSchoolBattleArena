#pragma once
#include <string>
#include <vector>
#include <WinSock2.h>

struct CreateThreadInfo {
	std::vector<SOCKET> sockets;
	int index;
};

class Server {

public:
	Server(const struct SERVER_CREATE_INFO* pCreateInfo);
	virtual ~Server() = default;

	virtual void Run() = 0;

protected:
	std::vector<SOCKET> sockets;

};




