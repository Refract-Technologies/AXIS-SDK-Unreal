#include "AxisRuntimeHandler.h"

#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Networking.h"

AxisRuntimeHandler::AxisRuntimeHandler()
{
	m_reader = MakeShared<FAxisRuntimeReader>();
	m_writer = MakeShared<FAxisRuntimeWriter>();
}
bool AxisRuntimeHandler::InitConnection()
{
	m_reader->InitConnection();
	m_writer->InitConnection();

	return true;
}

void AxisRuntimeHandler::Start()
{
	m_reader->StartThread();
	m_writer->StartThread();
}

void AxisRuntimeHandler::Stop()
{
	m_reader->StopThread();
	m_writer->StopThread();
	
	while (m_reader->ThreadAlive() || m_writer->ThreadAlive());
	
}

AxisRuntimeHandler::~AxisRuntimeHandler()
{

}

const TSharedPtr<FAxisRuntimeReader>& AxisRuntimeHandler::GetRuntimeReader()
{
	return m_reader;
}

const TSharedPtr<FAxisRuntimeWriter>& AxisRuntimeHandler::GetRuntimeWriter()
{
	return m_writer;
}

void AxisRuntimeHandler::GetNodeData(TArray<FQuat>& _nodeQuat, 
	TArray<FVector>& _nodeAccel) const
{
	m_reader->GetESPReader().GetNodeData(_nodeQuat, _nodeAccel);
}