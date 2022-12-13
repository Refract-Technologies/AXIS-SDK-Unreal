#pragma once

#include "IAxisEventHandler.h"
#include "AxisRuntimeReader.h"
#include "AxisRuntimeWriter.h"
#include <functional>

class AXIS_API AxisRuntimeEventHandler : public IAxisEventHandler
{
	TSharedPtr<FAxisRuntimeReader> m_reader;
	TSharedPtr<FAxisRuntimeWriter> m_writer;
	
public:
	AxisRuntimeEventHandler(const TSharedPtr<FAxisRuntimeReader>& _reader, const TSharedPtr<FAxisRuntimeWriter>& _writer);
	virtual ~AxisRuntimeEventHandler() = default;

	virtual bool IsESPConnected(const double _timeout = 0.2, const std::function<void()>& _eventFailue = {}) override;
	virtual bool IsHubConnected(const double _timeout = 0.2, const std::function<void()>& _eventFailure = {}) override;
	virtual bool IsRuntimeConnected(const double _timeout = 0.2, const std::function<void()>& _eventFailure = {}) override;
};