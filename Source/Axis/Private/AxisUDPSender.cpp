#include "AxisUDPSender.h"

void FAxisUDPSender::SendDataBuffer(uint8* _buffer, uint32 _size)
{

	
	{
		{
			FScopeLock lock(&m_mutex);
			m_writeLock = true;
			m_cmdLength = std::move(_size);
			memcpy(m_buffer, _buffer, m_cmdLength);
			m_writeLock = false;
		}
	}
}

FAxisUDPSender::FAxisUDPSender() :
	m_running{false},
	m_threadRunning{false},
	m_thread{nullptr},
	m_buffer{0}
{
}

bool FAxisUDPSender::Init()
{
	if (m_socket == nullptr)
	{
		return false;
	}
	m_threadRunning = true;
	return true;
}

void FAxisUDPSender::Exit()
{
	if (m_thread != nullptr)
	{
		
		delete m_thread;
		m_thread = nullptr;
		m_threadRunning = false;
	}
}

void FAxisUDPSender::Stop()
{
	m_threadRunning = false;
	m_running = false;
}

void FAxisUDPSender::StopThread()
{
	m_running = false;
}

uint32 FAxisUDPSender::Run()
{
	m_running = true;
	m_threadRunning = true;
	FIPv4Address ip = FIPv4Address::InternalLoopback;
	auto addr = m_endPoint.ToInternetAddr();
	while (m_running)
	{
		int32 sendBytes;
		{
			FScopeLock lock{ &m_mutex };
			if (m_cmdLength > 0)
			{
				m_socket->SendTo(m_buffer, m_cmdLength, sendBytes, *addr);

				if (sendBytes == 0)
				{
					
				}
			}
			m_writeLock = false;
			m_cmdLength = 0;
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

bool FAxisUDPSender::ThreadAlive()
{
	return m_threadRunning;
}

bool FAxisUDPSender::StartThread()
{
	m_thread = FRunnableThread::Create(this,
		TEXT("AxisUDPSenderThread"));
	return static_cast<bool>(m_thread);
}

bool FAxisUDPSender::IsRunning()
{
	return m_running;
}
