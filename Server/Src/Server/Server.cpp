#include "Server.h"

#include "ServerCreateInfo.h"
#include <thread>
#include <mutex>
#include <format>
#include <iostream>

static std::mutex createMTX;

void create_socket(CreateThreadInfo* info) {
	std::lock_guard<std::mutex> lock(createMTX);
	
	printf("creating socket %i...,", info->index);

	auto sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sk == INVALID_SOCKET) {
		printf("\tfailed..\ncould not create a socket for a server\n");
		return;
	}
	unsigned long mode = 1;
	auto result = ioctlsocket(sk, FIONBIO, &mode);
	if (result == SOCKET_ERROR) {
		printf("\t faild\ncould not set socket mode.\n");
		return;
	}
	// BIND THE SOCKET 
	printf("\tsocket created succsesfully.\n,");

	
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT + info->index);
	printf("binding socket %i... to server %i:%i", info->index, INADDR_ANY, PORT + info->index);
	result = bind(sk, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR) {
		printf("\t failed...");
		return;
	}

	printf("\tsocket bound succsesfully.\n,");
	info->sockets[info->index] = sk;
}


Server::Server(const SERVER_CREATE_INFO* pCreateInfo)
{
	unsigned long shouldBlock = pCreateInfo->isBlocking ? 0 : 1;
	
	sockets.resize(pCreateInfo->socket_count);

	CreateThreadInfo info{ };
	info.sockets = sockets;
	
	for (int i = 0; i < pCreateInfo->socket_count; i++)
	{
		info.index = i;
		// CREATE THE SOCKET 
		auto thread = new std::thread(create_socket, &info);
		thread->join();

	}

}

