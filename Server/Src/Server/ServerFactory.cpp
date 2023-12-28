#include "ServerFactory.h"

#include "MasterServer.h"

Server* ServerFactory::CreateServer(const SERVER_CREATE_INFO* pCreateInfo)
{
	switch (pCreateInfo->type)
	{
	case ServerType::Master:
		return new MasterServer(pCreateInfo);
	}
	printf("ERROR SERVER TYPE IS NOT RECOGNIZED.");
	return nullptr;

}
