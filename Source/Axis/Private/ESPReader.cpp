  #include "ESPReader.h"
#include <chrono>
#include <string>
#include <sstream>
#include "Windows/MinWindows.h"

static constexpr float qpoint_quat = 0.00006103f;  // calculated from Math.pow(2, -14);
static constexpr float qpoint_accl = 0.00390625f; // calculated from Math.pow(2, -8);

void ESPReader::UpdateReaderBuffer(const uint8* const _input, const uint32 _size)
{
	for (size_t i = 0; i < _size; ++i)
	{
		m_espReaderData[i] = _input[i];
	}
}

void ESPReader::GetNodeData(TArray<FQuat>& _nodeQuat, TArray<FVector>& _nodeAccel) const
{
	uint16 framePointer = 0;
	TArray<FQuat> tempNodeQuats;
	tempNodeQuats.Init(FQuat{0, 0, 0, 1}, _nodeQuat.Num());
	TArray<FVector> tempNodeAccel;
	tempNodeAccel.Init(FVector{ 0, 0, 0 }, _nodeQuat.Num());
	// populate node quats
	{
		for (uint16 i = 0; i < _nodeQuat.Num(); i++)
		{
			// Disregard node index
			framePointer += 1;

			tempNodeQuats[i].X = (*(int16*)(m_espReaderData.data() + framePointer)) * qpoint_quat; framePointer += 2; //6
			tempNodeQuats[i].Y = (*(int16*)(m_espReaderData.data() + framePointer)) * qpoint_quat; framePointer += 2; //8
			tempNodeQuats[i].Z = (*(int16*)(m_espReaderData.data() + framePointer)) * qpoint_quat; framePointer += 2; //10
			tempNodeQuats[i].W = (*(int16*)(m_espReaderData.data() + framePointer)) * qpoint_quat; framePointer += 2; //12

			// hard set r to 1.0f if all values are 0
			if (tempNodeQuats[i].X == 0.0f && tempNodeQuats[i].Y == 0.0f && tempNodeQuats[i].Z == 0.0f && tempNodeQuats[i].W == 0.0f) {
				tempNodeQuats[i].W = 1.0f;
			}
			tempNodeAccel[i].X = (*(int16*)(m_espReaderData.data() + framePointer)) * qpoint_accl; framePointer += 2;
			tempNodeAccel[i].Y = (*(int16*)(m_espReaderData.data() + framePointer)) * qpoint_accl; framePointer += 2;
			tempNodeAccel[i].Z = (*(int16*)(m_espReaderData.data() + framePointer)) * qpoint_accl; framePointer += 2;

		}

		{
			
			_nodeQuat = std::move(tempNodeQuats);
		}

		{
			_nodeAccel = std::move(tempNodeAccel);

		}
	}
}
