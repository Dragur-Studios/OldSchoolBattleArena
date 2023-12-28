#include <iostream>

#include <WinSock2.h>

#include "Server/ServerFactory.h"

int tcp_packet_size(SOCKET sock, _Out_ uint8_t* size) {

	char buffer[1];

	int err = recv(sock, buffer, 1, 0);
	
	if (err < 0)
		return err;

	size = (uint8_t*)buffer[0];
	
	return 0;
}

int tcp_recieve(SOCKET sock, char* buf, uint8_t size) {
	int total = 0;
	do {
		
		int ret = recv(sock, buf + total, size - total, 0);
		
		if (ret < 1)
			return ret;
		else 
			total += ret;


	} while (total < size);
	
	return total;
}

void HandleSingleCommunication() {
	// SOCKET
	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSock == INVALID_SOCKET) {
		printf("socket is incorrect");
		return;
	}

	
	// BIND
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);
	auto result = bind(listenSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR) {
		printf("Bind Failed");
		return;
	}

	// Listen , Client Connects, Accept Connection
	result = listen(listenSock, 1);
	if (result == SOCKET_ERROR) {
		printf("listen is Wrong.");
		return;
	}
	printf("Awaiting Connection...");

	auto comSocket = accept(listenSock, NULL, NULL);
	if (comSocket == SOCKET_ERROR) {
		printf("accept function wrong");
	}
	printf("Client Connected");

	uint8_t size = 0;
	result = tcp_packet_size(comSocket, &size);
	if (size > 0) {
		return;
	}

	char* buffer = new char[size];
	result = tcp_recieve(comSocket, (char*)buffer, size);
	
	printf("\n\n");
	printf(buffer);
	printf("\n\n");

	delete[] buffer;
	
	shutdown(listenSock, SD_BOTH);
	closesocket(listenSock);

	shutdown(comSocket, SD_BOTH);
	closesocket(comSocket);

}

const int MAX_SOCKETS = 64;


int main()
{
#if defined(PORT)
	printf("Found ENV VAR: PORT=%i\n\n", PORT);
#endif

	WSADATA wsadata;
	auto error = WSAStartup(WINSOCK_VERSION, &wsadata);
	if (error != 0) {
		std::cerr << "WSAStartup Failed!\n";
		return 1;
	}
	bool isActive = true;
	
	SERVER_CREATE_INFO createInfo{0};
	createInfo.isBlocking = false;
	createInfo.socket_count = 16;
	createInfo.type = ServerType::Master;

	auto masterServer = ServerFactory::CreateServer(&createInfo);
	masterServer->Run();

	return WSACleanup();
}