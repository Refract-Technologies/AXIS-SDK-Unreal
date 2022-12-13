#include "AxisUDPListener.h"

FAxisUDPListener::FAxisUDPListener() :
	m_running{ false },
	m_threadRunning{ false },
	m_thread{ nullptr }
{
}

bool FAxisUDPListener::Init()
{
	if (m_socket == nullptr)
	{
		return false;
	}
	m_threadRunning = true;
	return true;
}

void FAxisUDPListener::Exit()
{
	if (m_thread != nullptr)
	{
		delete m_thread;
		m_thread = nullptr;
		m_threadRunning = false;
	}
}

void FAxisUDPListener::Stop()
{
	m_threadRunning = false;
	m_running = false;
}

void FAxisUDPListener::StopThread()
{
	m_running = false;
}

uint32 FAxisUDPListener::Run()
{
	m_running = true;
	m_threadRunning = true;
	auto addr = m_endPoint.ToInternetAddr();
	while (m_running)
	{
		uint32 pendingDataSize;
		int32 readBytes;
		uint8 buffer[RECV_SIZE] = { 0 };

		if (m_socket->HasPendingData(pendingDataSize))
		{
			m_socket->RecvFrom(buffer, RECV_SIZE, readBytes,*addr);
			m_hasReceivedData = true;
			UpdateReadBuffer(buffer, readBytes);
		}
		else
		{
			m_hasReceivedData = false;
		}
	}

	if (m_socket != nullptr)
	{
		m_socket->Close();
		m_socketSubSystem->DestroySocket(m_socket);
		m_socket = nullptr;
	}

	return 0;
}

bool FAxisUDPListener::ThreadAlive()
{
	return m_threadRunning;
}


bool FAxisUDPListener::IsRunning()
{
	return m_running;
}

void FAxisUDPListener::StartThread()
{
	m_thread = FRunnableThread::Create(this,
		TEXT("AxisUDPListenerThread"));

}
