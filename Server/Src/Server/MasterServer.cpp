#include "MasterServer.h"

MasterServer::MasterServer(const SERVER_CREATE_INFO* pCreateInfo)
	: Server(pCreateInfo)
{
	printf("SERVER INITILIZED!");
}

MasterServer::~MasterServer()
{
}

void MasterServer::Run()
{
	int result = 0;
	
	while (active) {
		//system("cls");
		result = 0;

		PrintSocketsData();

		//fd_set readySet;
		//FD_ZERO(&readySet);
		//int i = 0;
		//for (const auto sk : sockets)
		//{
		//	printf("sk_%i awaiting connection", i);
		//	result = listen(sk, max_users_per_socket);

		//	if (result == SOCKET_ERROR) {
		//		printf("socket error.\n");
		//		active = false;
		//		break;
		//	}

		//	FD_SET(sk, &readySet);

		//	auto readFD = select(sockets.size(), &readySet, NULL, NULL, NULL);

		//	if (FD_ISSET(sk, &readySet)) {

		//	}
		//	
		//	/*if (comSocket == INVALID_SOCKET) {
		//		int ecode = WSAGetLastError();
		//		printf("communication socket is invalid.\n error code %i\n", ecode);
		//		active = false;
		//		break;
		//	}*/
		//	/*result = ioctlsocket(comSocket, FIONBIO, &mode);
		//	if (result == SOCKET_ERROR) {
		//		printf("socket error.");
		//		active = false;
		//		break;
		//	}*/

		//	printf("awaiting connections..\n");
		//	i++;

		//}

	}
}
