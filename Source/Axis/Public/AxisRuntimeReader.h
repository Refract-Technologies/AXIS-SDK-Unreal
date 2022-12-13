#pragma once


#include <CoreMinimal.h>
#include <HAL/Runnable.h>
#include <HAL/RunnableThread.h>

#include <IPAddress.h>
#include <AxisHelper.h>
#include <memory>
#include <array>
#include "ESPReader.h"
#include "HubLocalisationHandler.h"
#include "AxisUDPListener.h"

class AXIS_API FAxisRuntimeReader : public FAxisUDPListener
{

	static constexpr auto IMU_OP_MODE = 0x00;

	bool m_frameLock = false;

	uint8 m_buffer[AxisHelper::READ_BUFFER] = { 0 };
	
	uint32 m_bufferSize{ 0 };

	FRunnableThread* m_thread;
	uint32 HeaderPayload = 0x0F0F0F0F;

	ESPReader m_espReader;

	HubLocalisationReader m_hubReader;

	FCriticalSection m_frameBufferMutex;

	std::array<uint8, AxisHelper::READ_BUFFER> m_eventBuffer{0};
public:

	

	const std::array<uint8, AxisHelper::ESP_BUFFER_SIZE>& GetESPFrameData();

	const std::array<uint8, AxisHelper::HUB_BUFFER_SIZE>& GetHubFrameData();

	const std::array<uint8, AxisHelper::READ_BUFFER>& GetEventFrameData();

	void ClearEventFrameData();

	FAxisRuntimeReader();

	void UpdateReadBuffer(uint8* _outBuffer, int32 _outReadBytes) override;

	virtual bool InitConnection(uint32 _inPort = AxisHelper::LISTEN_PORT_NUM, FString _inIP = "127.0.0.1") override;

	virtual ~FAxisRuntimeReader() = default;

	const HubLocalisationReader& GetHubReader();
	const ESPReader& GetESPReader();
private:
	
	std::array<uint8,  AxisHelper::ESP_BUFFER_SIZE> m_espFrameData{};
	std::array<uint8,  AxisHelper::HUB_BUFFER_SIZE> m_hubFrameData{};
};