#pragma once

#include <CoreMinimal.h>
#include <HAL/Runnable.h>
#include <HAL/RunnableThread.h>

#include <IPAddress.h>
#include <Interfaces/IPv4/IPv4Endpoint.h>
#include <memory>

#include "AxisRuntimeWriter.h"
#include "AxisRuntimeReader.h"

class AXIS_API AxisRuntimeHandler 
{
	TSharedPtr<FAxisRuntimeReader> m_reader;
	TSharedPtr<FAxisRuntimeWriter> m_writer;

public:
	AxisRuntimeHandler();

	bool InitConnection();
	
	void Start();
	void Stop();

	virtual ~AxisRuntimeHandler();


	const TSharedPtr<FAxisRuntimeReader>& GetRuntimeReader();

	const TSharedPtr<FAxisRuntimeWriter>& GetRuntimeWriter();

	void GetNodeData(TArray<FQuat>& _nodeQuat, TArray<FVector>& _nodeAccel) const;
};