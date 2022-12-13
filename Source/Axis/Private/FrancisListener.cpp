#include "FrancisListener.h"
#include <string>

static const float qpoint_pos = 0.00006103f;  // calculated from Math.pow(2, -14);


bool FFrancisListener::GetPosition(FVector& _outPos)
{
	if (m_hasReceivedData && !m_lock)
	{

		m_lock = true;
		_outPos.X = *(float*)(m_francisBuffer.data() + 0);
		_outPos.Y = *(float*)(m_francisBuffer.data() + 4);
		_outPos.Z = *(float*)(m_francisBuffer.data() + 8);
		m_lock = false;

		return true;
	}

	return false;
}

void FFrancisListener::UpdateReadBuffer(uint8* _outBuffer, int32 _outReadBytes)
{
	if (m_lock)
	{
		return;
	}

	m_lock = true;

	// maybe should throw an assert to prevent error
	// take the data and copy to its own buffer
	m_bufferSize = _outReadBytes;
	for (size_t i = 0; i < _outReadBytes; ++i)
	{
		m_francisBuffer[i] = _outBuffer[i];
	}
	m_lock = false;
}
