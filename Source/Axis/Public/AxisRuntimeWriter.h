#pragma once

#include <CoreMinimal.h>
#include <HAL/Runnable.h>
#include <HAL/Runnable.h>
#include <HAL/RunnableThread.h>

#include <IPAddress.h>
#include <Interfaces/IPv4/IPv4Endpoint.h>
#include <memory>

#include "AxisUDPSender.h"

class AXIS_API FAxisRuntimeWriter : public FAxisUDPSender
{

	static constexpr uint8 FRAME_SIZE = 148;

	static constexpr uint32 SENDER_PORT_NUM = 45068;

	FSocket* m_senderSocket;
	bool m_threadRunning = false;
	bool m_frameLock = false;
	bool m_running = false;
	bool m_writeLock = false;

	uint8 m_writeBuffer[FRAME_SIZE] = { 0 };

	FRunnableThread* m_thread;

public:

	void Write(uint8* _cmd, const uint8 _length);
	virtual ~FAxisRuntimeWriter() = default; 

	virtual bool InitConnection(uint32 _inPort = SENDER_PORT_NUM, FString _inIP = "127.0.0.1");

	//void StartThread();
};