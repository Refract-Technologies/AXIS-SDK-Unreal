#pragma once

#include "CoreMinimal.h"
#include <string>
#include <array>
#include <AxisHelper.h>
class AXIS_API ESPReader
{
	
	std::array<uint8, AxisHelper::ESP_BUFFER_SIZE> m_espReaderData{};

public:
	void UpdateReaderBuffer(const uint8* const _input, const uint32 _size);
	
	void GetNodeData(TArray<FQuat>& _nodeQuat, TArray<FVector>& _nodeAccel) const;
};