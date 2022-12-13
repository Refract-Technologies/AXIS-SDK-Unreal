#pragma once

#include "CoreMinimal.h"
#include "Axis_Enums.h"

namespace AxisHelper
{

	static constexpr uint32 LISTEN_PORT_NUM = 45069;

	//packet size to receive from axis runtim
	static constexpr auto READ_BUFFER = 284;

	static constexpr auto HEADER_BYTE = 4;
	static constexpr auto OP_MODE_BYTE = 1;
	static constexpr auto PAYLOAD_BYTE = 1;

	static constexpr auto HUB_BUFFER_SIZE = 28;

	static constexpr auto HEADER_OP_MODE_PAYLOAD_BYTE_OFFSET = HEADER_BYTE + OP_MODE_BYTE + PAYLOAD_BYTE;
	//Should return 256
	//ESP size will change in the future, so just take the remainder of read buffer and minus everything.
	static constexpr auto ESP_BUFFER_SIZE = READ_BUFFER - HUB_BUFFER_SIZE - HEADER_OP_MODE_PAYLOAD_BYTE_OFFSET;

	
	static constexpr auto HEADER_AND_ESP_OFFSET = HEADER_OP_MODE_PAYLOAD_BYTE_OFFSET + ESP_BUFFER_SIZE;
	FQuat DoAxisNodeCorrection(const EAxisPartEnum& _nodes, const FQuat& _quat);


}