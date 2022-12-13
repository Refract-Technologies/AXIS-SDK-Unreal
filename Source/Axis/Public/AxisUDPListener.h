#pragma once

#include "AxisUDPConnector.h"

class AXIS_API FAxisUDPListener : public FAxisUDPConnector
{
	bool m_running;
	bool m_threadRunning;
	FRunnableThread* m_thread;

protected:
	bool m_hasReceivedData = false;

public:
	FAxisUDPListener();
	virtual bool Init() override;
	virtual void Exit() override;
	virtual void Stop() override;
	virtual uint32 Run() override;

	virtual ~FAxisUDPListener() = default;
	bool ThreadAlive();
	bool IsRunning();
	void StartThread();
	void StopThread();

	
	virtual void UpdateReadBuffer(uint8* _outBuffer, int32 _outReadBytes) = 0;
};