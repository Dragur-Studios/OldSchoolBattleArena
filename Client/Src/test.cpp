#include <iostream>

#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

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

int tcp_send(SOCKET sock, char* data, uint8_t size) {
	int result=0;
	int sent = 0;
	while (sent < size) {
		result = send(sock, (const char*)data + sent, size - sent, 0);
		
		if (result <= 0)
			return result;
		
		sent += result;
	}
}

void HandleSingleCommunication() {
	
	auto comSock = socket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP);

	if (comSock == INVALID_SOCKET) {
		printf("Invalid Socket.");
		return;
	}

	// Connect.
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(5000);

	int result = connect(comSock, (SOCKADDR*)&addr, sizeof(addr));
	if (result == SOCKET_ERROR) {
		printf("Error, Could not connect.");
		return;
	}
	


}



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

	HandleSingleCommunication();

	return WSACleanup();
}