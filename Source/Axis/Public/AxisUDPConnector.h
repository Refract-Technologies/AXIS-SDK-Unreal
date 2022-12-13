#pragma once

#include <CoreMinimal.h>
#include <HAL/Runnable.h>
#include <HAL/RunnableThread.h>


#include <IPAddress.h>

#include <Interfaces/IPv4/IPv4Endpoint.h>
#include <memory>


#include "Networking.h"

class AXIS_API FAxisUDPConnector : public FRunnable
{
protected:
	static constexpr int RECV_SIZE = 1024;
	bool m_running = false;
	FSocket* m_socket = nullptr;
	ISocketSubsystem* m_socketSubSystem;
	FIPv4Endpoint m_endPoint;
public:
	virtual bool InitConnection(uint32 _inPort, FString _inIP = "127.0.0.1");

	
	virtual ~FAxisUDPConnector() = default;
};