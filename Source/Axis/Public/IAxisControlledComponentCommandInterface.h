#pragma once
#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include "Containers/UnrealString.h"

class IAxisControlledComponentCommandInterface 
{
public:
	// Virtual deconstructor
	virtual ~IAxisControlledComponentCommandInterface() {}

	//
	// Core Commands
	//

	virtual bool CalibrateNodes() = 0;
	virtual bool ResetHub() = 0;
	virtual bool ZeroNodes() = 0;

	//
	// Extra Commands
	//
	virtual bool VibrateNode(uint8 index, uint8 intensity, uint8 duration) = 0;
	virtual bool FlashNodeLED(uint8 index, uint8 red, uint8 green, uint8 blue) = 0;

	virtual void StartStreaming() = 0;
	virtual void StopStreaming() = 0;
};