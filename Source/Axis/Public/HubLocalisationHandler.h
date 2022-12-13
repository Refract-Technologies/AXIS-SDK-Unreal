#pragma once

#include "CoreMinimal.h"
#include <array>
#include <AxisHelper.h>

class AXIS_API HubLocalisationReader
{	
	std::array<uint8, AxisHelper::HUB_BUFFER_SIZE> m_hubFrameData{};

	FVector m_lastFramePosition;
	float m_posDeltaX;
	float m_posDeltaY;
	float m_posDeltaZ;

	float m_maxPosDeltaX;
	float m_maxPosDeltaY;
	float m_maxPosDeltaZ;

	

	void CalculatePositionDelta(FVector _currentPosition);
public:

	const bool GetHubDataFrame(FVector& _position, FQuat& _rotation, FQuat& rawRot) const;
	
	void UpdateHubBuffer(const uint8* const _input, const uint32 _size);

};