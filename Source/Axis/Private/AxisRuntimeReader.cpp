#include "AxisRuntimeReader.h"

#include "Networking.h"

const std::array<uint8, AxisHelper::ESP_BUFFER_SIZE>& FAxisRuntimeReader::GetESPFrameData()
{
	return m_espFrameData;
}


const std::array<uint8, AxisHelper::HUB_BUFFER_SIZE>& FAxisRuntimeReader::GetHubFrameData()
{
	return m_hubFrameData;
}

const std::array<uint8, AxisHelper::READ_BUFFER>& FAxisRuntimeReader::GetEventFrameData()
{
	return m_eventBuffer;
}

void FAxisRuntimeReader::ClearEventFrameData()
{
	m_eventBuffer[0] = 0;
}


FAxisRuntimeReader::FAxisRuntimeReader()
{
}


void FAxisRuntimeReader::UpdateReadBuffer(uint8* _outBuffer, int32 _outReadBytes)
{
	m_frameLock = true;
	uint8 headerCheck[4];
	memcpy(headerCheck, _outBuffer, 4);

	if (*reinterpret_cast<uint32*>(headerCheck) == HeaderPayload)
	{
		{
			FScopeLock lock(&m_frameBufferMutex);
			memcpy(m_buffer, _outBuffer, _outReadBytes);
		}
		
		uint8 opModeCheck;
		memcpy(&opModeCheck, m_buffer + AxisHelper::HEADER_BYTE, AxisHelper::OP_MODE_BYTE);
		if (opModeCheck == IMU_OP_MODE)
		{
			m_espReader.UpdateReaderBuffer(m_buffer + AxisHelper::HEADER_OP_MODE_PAYLOAD_BYTE_OFFSET, AxisHelper::ESP_BUFFER_SIZE);

			m_hubReader.UpdateHubBuffer(m_buffer + AxisHelper::HEADER_AND_ESP_OFFSET, AxisHelper::HUB_BUFFER_SIZE);
		}
		else
		{
			std::copy(std::cbegin(m_buffer) + AxisHelper::HEADER_BYTE, std::cend(m_buffer), m_eventBuffer.data());
		}
	}
	m_frameLock = false;
}

const HubLocalisationReader& FAxisRuntimeReader::GetHubReader()
{
	return m_hubReader;
}
const ESPReader& FAxisRuntimeReader::GetESPReader()
{
	return m_espReader;
}
bool FAxisRuntimeReader::InitConnection(uint32 _inPort, FString _inIP)
{
	if (m_socket != nullptr)
	{
		return false;
	}
	//we want local address
	FIPv4Address ip = FIPv4Address::InternalLoopback;
	m_socketSubSystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	auto addr = m_socketSubSystem->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(AxisHelper::LISTEN_PORT_NUM);

	return FAxisUDPConnector::InitConnection(AxisHelper::LISTEN_PORT_NUM, ip.ToString());
}
