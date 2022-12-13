#include "PlayerLocationResolver.h"
#include "AxisConfig.h"


PlayerLocationResolver::PlayerLocationResolver()
{
	
	GameDistY = 300;
	GameDistX = 300;

	GameDistXOffset = GameDistX;

	//INIT ARRAYS
	FBoundary.Init(TArray<float>{0, 0, 0}, 4);
	ARCBoundary.Init(TArray<float>{0, 0, 0}, 4);

	// Set Default Boundaries
	FBoundary[0][0] = 0.2f;
	FBoundary[0][1] = 0.8f;
	FBoundary[0][2] = 0.0f;

	FBoundary[1][0] = 0.8f;
	FBoundary[1][1] = 0.8f;
	FBoundary[1][2] = 0.0f;

	FBoundary[2][0] = 0.4f;
	FBoundary[2][1] = 0.2f;
	FBoundary[2][2] = 0.0f;

	FBoundary[3][0] = 0.6f;
	FBoundary[3][1] = 0.2f;
	FBoundary[3][2] = 0.0f;
}

PlayerLocationResolver::~PlayerLocationResolver()
{

}


void PlayerLocationResolver::InitListeners(FFrancisListener* _extListener, HubLocalisationReader* _intListener)
{
	m_extListener = _extListener;
	m_intListener = _intListener;

	CalculateExtValues();
}
void PlayerLocationResolver::InitListeners(TSharedPtr<FFrancisListener>_extListener, const HubLocalisationReader& _intListener)
{
	m_extListener = _extListener.Get();
	m_intListener = &_intListener;

	CalculateExtValues();
}
void PlayerLocationResolver::SetExternalScreenSpaceBoundary(FVector& inPosition, int loc)
{
	FBoundary[loc][0] = inPosition.X;
	FBoundary[loc][1] = inPosition.Y;
	FBoundary[loc][2] = inPosition.Z;

	cornersCalibrated = 0;
	for (int i = 0; i < FBoundary.Num(); ++i) 
	{
		if (FBoundary[i][0] != 0.0f)
		{
			cornersCalibrated += 1;
		}
	}

	if (cornersCalibrated >= 4) {
		CalculateExtValues();
	}
}

void PlayerLocationResolver::CalculateExtValues()
{
	// F Y Dist (top btm / foward(front) backward(back))
	mat_LeftEdgeLength = std::abs(FBoundary[0][1] - FBoundary[2][1]); // btm left - top left (left edge dist)
	mat_RightEdgeLength = std::abs(FBoundary[1][1] - FBoundary[3][1]); // btm right - top right (right edge dist)
	// Find Average :: Assume symmetery btw Left and Right
	mat_LeftRightEdgeLengthAverage = ((mat_LeftEdgeLength + mat_RightEdgeLength) / 2 ) * -1; // we want it in negative value
	
	mat_FarEdgeYPosAverage = (FBoundary[2][1] + FBoundary[3][1]) / 2;

	// F X Dist (left right)
	mat_NearEdgeLength = std::abs(FBoundary[1][0] - FBoundary[0][0]); // btm right - btm left (near edge dist)
	mat_FarEdgeLength= std::abs(FBoundary[3][0] - FBoundary[2][0]); // top right - top left (far edge dist)

	// Calculate scale factor (mat_NearToFarScaleFactor)
	mat_NearToFarScaleFactor = std::abs(mat_NearEdgeLength / mat_FarEdgeLength) - 1;
	// Remove the 1 to add back in later
}


// Called every frame - main resolver function
bool PlayerLocationResolver::ResolveFinalPlayerPositionAndRotation(FVector& inPosition, FQuat& inRotation, FQuat& inRotationRaw)
{
	FVector resolvedExtPos = FVector::ZeroVector;
	bool extDataReceived = false;
	if (AxisConfig::useOutsideInTracking)
	{
		// get ext position (Francis)
		FVector rawExtPos = FVector(0.0f, 0.0f, 0.0f);
		extDataReceived = m_extListener->GetPosition(rawExtPos);

		// === Resolving EXT Pos ===
		// Calculate scale factor to know how much to scale along X axis based on Y axis value
		float scaled_ScaleFactor = (rawExtPos.Y * mat_NearToFarScaleFactor) + 1;

		// Calculate player new x pos
		// need to multiply X by the scaled scale factor
		// as the player goes further back, his X should be modified more
		// if player is nearer, we treat movement on 1:1 scale
		float playerXNormalised = (rawExtPos.X - FBoundary[0][0]) / mat_NearEdgeLength;
		float playerXFinalPos = ((GameDistX * playerXNormalised * scaled_ScaleFactor) - GameDistXOffset) * 0.1;

		// Get player Y
		float playerYNormalised = (rawExtPos.Y - mat_FarEdgeYPosAverage) / mat_LeftRightEdgeLengthAverage;
		float playerYFinalPos = ((GameDistY * playerYNormalised + GameDistY) * -0.1);

		resolvedExtPos = FVector(playerXFinalPos, playerYFinalPos, 0.0f);
	}


	// get int position (AR Core)
	FVector rawIntPos = FVector::ZeroVector;
	FQuat rawIntRot = FQuat::Identity;
	FQuat rawRotOffSet = FQuat::Identity;

	bool intDataReceived = false;
	if (AxisConfig::useInsideOutTracking) 
	{		
		intDataReceived = m_intListener->GetHubDataFrame(rawIntPos, rawIntRot, rawRotOffSet);
	}

	//
	// Blend EXT and INT values?
	//
	// Should return last known location instead of zero vector?
	FVector finalPos = FVector(0.0f, 0.0f, 0.0f);
	if (AxisConfig::useOutsideInTracking && AxisConfig::useInsideOutTracking)
	{
		if (extDataReceived && intDataReceived) {
			finalPos = FVector(
				(resolvedExtPos.X + rawIntPos.X / 2),
				(resolvedExtPos.Y + rawIntPos.Y / 2),
				rawIntPos.Z
			);
		}
		else if (extDataReceived) {
			finalPos = FVector(resolvedExtPos.X, resolvedExtPos.Y, finalPos.Z);
		}
		else if (intDataReceived) {
			finalPos = FVector(rawIntPos.X, rawIntPos.Y, rawIntPos.Z);
		}
	}
	else if (AxisConfig::useInsideOutTracking) {
		finalPos = intDataReceived ? FVector(rawIntPos.X, rawIntPos.Y, rawIntPos.Z) : FVector::ZeroVector;
	}
	else if (AxisConfig::useOutsideInTracking) {
		finalPos = extDataReceived ? FVector(resolvedExtPos.X, resolvedExtPos.Y, finalPos.Z) : FVector::ZeroVector;
	}

	if (FMath::IsNaN(finalPos.X) || FMath::IsNaN(finalPos.Y) || FMath::IsNaN(finalPos.Z)) {
		return false;
	}

	{
		FScopeLock lock(&m_hubDataMutex);
		inPosition = FVector(finalPos.X, finalPos.Y, finalPos.Z);
		if (!FMath::IsNaN(rawIntRot.X) && !FMath::IsNaN(rawIntRot.Y) && !FMath::IsNaN(rawIntRot.Z) && !FMath::IsNaN(rawIntRot.W)) {
			inRotation = FQuat(rawIntRot);
			inRotationRaw = FQuat{ rawRotOffSet };
		}
	}

	return true;
}