#pragma once

#include <CoreMinimal.h>


struct AXIS_API AxisNodeData
{
	FQuat m_rotation;
	FVector m_acceleration;
};

struct AXIS_API AxisHubData
{
	FQuat m_rotation;
	FVector m_absolutePosition;
};