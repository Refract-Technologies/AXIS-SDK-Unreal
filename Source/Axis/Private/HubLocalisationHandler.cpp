#include "HubLocalisationHandler.h"

void HubLocalisationReader::CalculatePositionDelta(FVector _currentPosition)
{
	m_posDeltaX = abs(m_lastFramePosition.X - _currentPosition.X);
	m_posDeltaY = abs(m_lastFramePosition.Y - _currentPosition.Y);
	m_posDeltaZ = abs(m_lastFramePosition.Z - _currentPosition.Z);

	m_maxPosDeltaX = m_maxPosDeltaX > m_posDeltaX ? m_maxPosDeltaX : m_posDeltaX;
	m_maxPosDeltaY = m_maxPosDeltaY > m_posDeltaY ? m_maxPosDeltaY : m_posDeltaY;
	m_maxPosDeltaZ = m_maxPosDeltaZ > m_posDeltaZ ? m_maxPosDeltaZ : m_posDeltaZ;

	m_lastFramePosition = _currentPosition;
}
const bool HubLocalisationReader::GetHubDataFrame(FVector& _position, FQuat& _rotation, FQuat& _rawRot) const
{
	uint32 framePointer = 0;


	float absRotationX = *(float*)((m_hubFrameData.data() + framePointer)); framePointer += 4;
	float absRotationY = *(float*)((m_hubFrameData.data() + framePointer)); framePointer += 4;
	float absRotationZ = *(float*)((m_hubFrameData.data() + framePointer)); framePointer += 4;
	float absRotationW = *(float*)((m_hubFrameData.data() + framePointer)); framePointer += 4;

	float absPosX = *(float*)((m_hubFrameData.data() + framePointer)); framePointer += 4;
	float absPosY = *(float*)((m_hubFrameData.data() + framePointer)); framePointer += 4;
	float absPosZ = *(float*)((m_hubFrameData.data() + framePointer)); framePointer += 4;


	if (absRotationX == 0 && absRotationY == 0 && absRotationZ == 0 && absRotationW == 0)
	{
		return false;
	}
	if (FMath::IsNaN(absPosX) || FMath::IsNaN(absPosY) || FMath::IsNaN(absPosZ))
	{
		return false;
	}

	if (FMath::IsNaN(absRotationX) || FMath::IsNaN(absRotationY) || FMath::IsNaN(absRotationZ) || FMath::IsNaN(absRotationW))
	{
		
		return false;
	}

	_position = std::move(FVector(-absPosX, -absPosZ, absPosY) * 10.0f);
	_rotation = std::move(FQuat(absRotationX, absRotationY, absRotationZ, absRotationW));
	_rawRot = std::move(FQuat{ absRotationX, absRotationY, absRotationZ, absRotationW });
	return true;


}

void HubLocalisationReader::UpdateHubBuffer(const uint8* const _input, const uint32 _size)
{
	for (size_t i = 0; i < _size; ++i)
	{
		m_hubFrameData[i] = _input[i];
	}
}
