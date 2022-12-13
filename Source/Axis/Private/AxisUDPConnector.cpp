#include "AxisUDPConnector.h"


#include "Networking.h"

bool FAxisUDPConnector::InitConnection(uint32 _inPort, FString _inIP)
{
	if (m_socket != nullptr)
	{
		return false;
	}
	m_socketSubSystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	FIPv4Address deviceAddr;
	FIPv4Address::Parse(_inIP, deviceAddr);
	auto addr = m_socketSubSystem->CreateInternetAddr();
	addr->SetIp(deviceAddr.Value);
	addr->SetPort(_inPort);
	
	m_endPoint = FIPv4Endpoint(addr);

	const FString Description = "AXIS LISTENING Socket";
	m_socket = m_socketSubSystem->CreateSocket(NAME_DGram, *Description, true);

	if (m_endPoint.Address.IsMulticastAddress())
	{
		m_socket = FUdpSocketBuilder(TEXT("AXIS Connector"))
			.AsNonBlocking()
			.AsReusable()
			.BoundToPort(_inPort)
			.WithReceiveBufferSize(0)
			.WithSendBufferSize(0)
			.BoundToAddress(FIPv4Address::InternalLoopback)
			.JoinedToGroup(m_endPoint.Address)
			.WithMulticastLoopback()
			.WithMulticastTtl(2);

	}
	else
	{
		bool Error = !m_socket->SetNonBlocking(!false) ||
			!m_socket->SetReuseAddr(false) ||
			!m_socket->SetBroadcast(false) ||
			!m_socket->SetRecvErr();

		if (!Error)
		{
			bool allGood = !m_socket->Bind(*m_endPoint.ToInternetAddr());
			ESocketErrors sockError = ESocketErrors::SE_NO_ERROR;
			Error = !allGood;
			if (Error)sockError = m_socketSubSystem->GetLastErrorCode();
		}

		if (!Error)
		{
			int32 OutNewSize;

			m_socket->SetReceiveBufferSize(RECV_SIZE, OutNewSize);
			m_socket->SetSendBufferSize(RECV_SIZE, OutNewSize);
		}

	}
	
	return true;
}
