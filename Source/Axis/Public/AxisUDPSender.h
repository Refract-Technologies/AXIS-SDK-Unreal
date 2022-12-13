#pragma once

#include "AxisUDPConnector.h"

class AXIS_API FAxisUDPSender : public FAxisUDPConnector
{
	bool m_running;
	bool m_threadRunning;
	bool m_writeLock;
	FRunnableThread* m_thread;
	uint8 m_buffer[148];

	uint32 m_cmdLength;
protected:
	FCriticalSection m_mutex;

public:

	void SendDataBuffer(uint8* _buffer,uint32 _size);
	FAxisUDPSender();
	virtual bool Init() override;
	virtual void Exit() override;
	virtual void Stop() override;

	virtual uint32 Run() override;

	virtual ~FAxisUDPSender() = default;

	bool ThreadAlive();
	bool StartThread();
	bool IsRunning();
	void StopThread();
};