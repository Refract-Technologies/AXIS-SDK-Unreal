#pragma once

#include "CoreMinimal.h"
#include <functional>
class AXIS_API IAxisEventHandler
{
public:

	virtual bool IsESPConnected(const double _timeout = 0.2, const std::function<void()>& _eventFailue = {}) = 0;
	virtual bool IsHubConnected(const double _timeout = 0.2, const std::function<void()>& _eventFailue = {}) = 0;
	virtual bool IsRuntimeConnected(const double _timeout = 0.2, const std::function<void()>& _eventFailue = {}) = 0;

	virtual ~IAxisEventHandler() = default;
};