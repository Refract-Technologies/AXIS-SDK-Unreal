#pragma once

#include "CoreMinimal.h"
#include "FrancisListener.h"
#include "HubLocalisationHandler.h"

class PlayerLocationResolver
{
public:
	PlayerLocationResolver();
	~PlayerLocationResolver();

	

	void InitListeners(FFrancisListener* _extListener, HubLocalisationReader* _intListener);
	void InitListeners(TSharedPtr<FFrancisListener> _extListener, const HubLocalisationReader& _intListener);

	void SetExternalScreenSpaceBoundary(FVector& inPosition, int location);
	

	bool ResolveFinalPlayerPositionAndRotation(FVector& _position, FQuat& _rotation, FQuat& _rotationRaw);
private:
	void CalculateExtValues();

	FFrancisListener* m_extListener;
	const HubLocalisationReader* m_intListener;

	// [0] Bottom Left [x,y,z]
	// [1] Bottom Right
	// [2] Top Left
	// [3] Top Right
	TArray<TArray<float>> FBoundary;
	TArray<TArray<float>> ARCBoundary;

	// UNREAL AXIS SYSTEM
	// Z is Up/Down
	// Y is Forward/Backward
	// X is Left/Right
	float GameDistX;
	float GameDistY;
	float GameDistXOffset;

	float mat_NearEdgeLength;
	float mat_FarEdgeLength;
	float mat_LeftEdgeLength;
	float mat_RightEdgeLength;
	float mat_LeftRightEdgeLengthAverage;
	float mat_NearToFarScaleFactor;
	float mat_FarEdgeYPosAverage;

	int cornersCalibrated = 0;

	FCriticalSection m_hubDataMutex;
};
