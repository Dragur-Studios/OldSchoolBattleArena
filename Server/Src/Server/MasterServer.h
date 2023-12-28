#pragma once

#include "./Server.h"

class MasterServer : public Server
{
public:
	MasterServer(const struct SERVER_CREATE_INFO* pCreateInfo);
	~MasterServer();
	
	virtual void Run() override;

private:
	bool active;

	const int max_users_per_socket = 16;

};

