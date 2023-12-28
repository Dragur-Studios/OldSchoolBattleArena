#pragma once

#include "Server.h"
#include "ServerCreateInfo.h"

static class ServerFactory {
public:
	static Server* CreateServer(const SERVER_CREATE_INFO* pCreateInfo);
};