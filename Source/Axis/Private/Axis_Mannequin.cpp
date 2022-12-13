#include "Axis_Mannequin.h"

UAxis_Mannequin::UAxis_Mannequin() :
	m_hubMultiplier{10.0f},
	m_updatePosition{true},
	m_updateHubRotation{true},
	m_updateNodes{true}

{
	PrimaryComponentTick.bCanEverTick = true;
	m_nodeQuat.Init({ 0,0,0,1 }, 16);
	m_nodeAcceleration.Init({ 0,0,0 }, 16);
	m_hubRotationRaw = FQuat::Identity;
	m_hubRotationOffsetRaw = FQuat::Identity;
}

void UAxis_Mannequin::UpdateNodeData(const TArray<FQuat>& _nodeQuat, 
	const TArray<FVector>& _nodeAccel)
{
	m_nodeQuat = _nodeQuat;
	m_nodeAcceleration = _nodeAccel;
}
void UAxis_Mannequin::UpdateHubRotation(const FQuat& _hubRotationRaw, const FQuat& _hubRotationOffset)
{
	m_hubRotationRaw = _hubRotationRaw;
	m_hubRotationOffsetRaw = _hubRotationOffset;
}

void UAxis_Mannequin::UpdateHubPosition(const FVector& _positionOffset)
{
	m_hubPosition = _positionOffset * FVector{ -m_hubMultiplier, -m_hubMultiplier,m_hubMultiplier };
}

void UAxis_Mannequin::BeginPlay()
{
	Super::BeginPlay();
	m_positionOffset = GetOwner()->GetActorLocation();
}

void UAxis_Mannequin::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector newPosition = m_positionOffset + m_hubPosition;

	GetOwner()->SetActorLocation(newPosition);
}

