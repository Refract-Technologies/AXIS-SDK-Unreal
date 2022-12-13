#include "AxisHelper.h"

namespace AxisHelper
{
	FQuat DoAxisNodeCorrection(const EAxisPartEnum& _nodes, const FQuat& _quat)
	{
		switch (_nodes)
		{
		case HUB:
			return std::move(FQuat{ _quat.X, _quat.Z,_quat.Y, -_quat.W });
		case THIGH_L:
		case THIGH_R:
			return std::move(FQuat{ -_quat.X,_quat.Y,-_quat.Z,_quat.W });	

		case CALF_L:
		case CALF_R:
		case UPPERARM_L:
		case UPPERARM_R:
		case LOWERARM_L:
		case LOWERARM_R:
			
		case HEAD:
			return std::move(FQuat{ _quat.X,-_quat.Y,-_quat.Z,_quat.W });
		
		default:

			return std::move(FQuat{ _quat });
		}
	}
	
}