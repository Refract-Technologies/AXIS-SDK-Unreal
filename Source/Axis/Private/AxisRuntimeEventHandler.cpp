#include "AxisRuntimeEventHandler.h"
#include <chrono>

AxisRuntimeEventHandler::AxisRuntimeEventHandler(const TSharedPtr<FAxisRuntimeReader>& _reader, const TSharedPtr<FAxisRuntimeWriter>& _writer) :
	m_reader{_reader},
	m_writer{_writer}
{
}

bool AxisRuntimeEventHandler::IsESPConnected(const double _timeout, const std::function<void()>& _eventFailure)
{
	//send event first den get event msg		
	uint8 cmd[] = { 0x01,0xD0 };

	m_writer->Write(cmd, sizeof(cmd));

	const auto& eventBuffer = m_reader->GetEventFrameData();
	auto start = std::chrono::system_clock::now();
	while (m_reader->GetEventFrameData()[0] != 0xD0)
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		if (elapsed_seconds.count() >= _timeout)
		{
			
			_eventFailure();
			return false;
		}
	}

	m_reader->ClearEventFrameData();
	return static_cast<bool>(m_reader->GetEventFrameData()[2]);
}

bool AxisRuntimeEventHandler::IsHubConnected(const double _timeout,const std::function<void()>& _eventFailure)
{
	uint8 cmd[] = { 0x01,0xD1 };

	m_writer->Write(cmd, sizeof(cmd));

	const auto& eventBuffer = m_reader->GetEventFrameData();

	auto start = std::chrono::system_clock::now();
	while (m_reader->GetEventFrameData()[0] != 0xD1)
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		if (elapsed_seconds.count() >= (_timeout))
		{
			
			_eventFailure();
			return false;
		}
	}

	m_reader->ClearEventFrameData();
	return static_cast<bool>(m_reader->GetEventFrameData()[2]);
}

bool AxisRuntimeEventHandler::IsRuntimeConnected(const double _timeout, const std::function<void()>& _eventFailure)
{
	uint8 cmd[] = { 0x01,0xCA };

	m_writer->Write(cmd, sizeof(cmd));

	const auto& eventBuffer = m_reader->GetEventFrameData();

	auto start = std::chrono::system_clock::now();
	while (m_reader->GetEventFrameData()[0] != 0xCA)
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		if (elapsed_seconds.count() >= _timeout)
		{
			
			_eventFailure();
			return false;
		}
	}

	m_reader->ClearEventFrameData();
	return static_cast<bool>(m_reader->GetEventFrameData()[2]);
}
