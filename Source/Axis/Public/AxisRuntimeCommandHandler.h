#pragma once
#include "CoreMinimal.h"
#include "IAxisControlledComponentCommandInterface.h"
#include "AxisRuntimeWriter.h"

class AXIS_API AxisRuntimeCommandHandler : public IAxisControlledComponentCommandInterface
{
public:

	AxisRuntimeCommandHandler(const TSharedPtr<FAxisRuntimeWriter>& _writer);
	virtual ~AxisRuntimeCommandHandler() = default;


	//
	// Core Commands
	//
	virtual bool CalibrateNodes() override;
	virtual bool ZeroNodes() override;
	virtual bool ResetHub() override;
	//
	// Extra Commands
	//
	virtual bool VibrateNode(uint8 index, uint8 intensity, uint8 duration)override;
	virtual bool FlashNodeLED(uint8 index, uint8 red, uint8 green, uint8 blue)override;
	virtual void StartStreaming() override;
	virtual void StopStreaming() override;

private:

	TSharedPtr<FAxisRuntimeWriter>  m_writer;
};