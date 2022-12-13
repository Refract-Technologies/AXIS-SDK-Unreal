#pragma once
#include "AxisUDPListener.h"
#include <array>

class AXIS_API FFrancisListener : public FAxisUDPListener
{
	static constexpr auto FRANCIS_BUFFER_SIZE = 12;
	std::array<uint8, FRANCIS_BUFFER_SIZE> m_francisBuffer{};
	
	bool m_lock = false;
	uint32 m_bufferSize = 0;
public:
	bool GetPosition(FVector& _outPos);
	virtual void UpdateReadBuffer(uint8* _outBuffer, int32 _outReadBytes) override;
};