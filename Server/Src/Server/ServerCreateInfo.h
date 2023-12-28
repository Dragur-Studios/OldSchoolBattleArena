#pragma once

enum class ServerType {
	Master,
	__COUNT__,
	NONE = -1,
};
struct SERVER_CREATE_INFO {
	int socket_count = 0;
	enum ServerType type = ServerType::NONE;
	bool isBlocking = true;
};
