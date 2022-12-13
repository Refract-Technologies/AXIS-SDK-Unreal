#include "AxisRuntimeWriter.h"

void FAxisRuntimeWriter::Write(uint8* _cmd, const uint8 _length)
{     
    SendDataBuffer(_cmd, _length);
}

bool FAxisRuntimeWriter::InitConnection(uint32 _inPort, FString _inIP)
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
    addr->SetPort(SENDER_PORT_NUM);

    return FAxisUDPConnector::InitConnection(SENDER_PORT_NUM, ip.ToString());

}
