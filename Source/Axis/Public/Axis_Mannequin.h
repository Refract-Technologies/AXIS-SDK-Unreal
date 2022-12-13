#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h" 
#include "Axis_Enums.h"

#include "Axis_Mannequin.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AXIS_API UAxis_Mannequin : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float m_hubMultiplier;
public:

	UPROPERTY(EditAnywhere)
	bool m_updatePosition;	

	UPROPERTY(EditAnywhere)
		bool m_updateHubRotation;

	UPROPERTY(EditAnywhere)
	bool m_updateNodes;

	UAxis_Mannequin();

	TArray<FQuat> m_nodeQuat;
	TArray<FVector> m_nodeAcceleration;
	

	FQuat m_hubRotationRaw;
	FQuat m_hubRotationOffsetRaw;

	//Cache the starting position of the actor
	FVector m_positionOffset;
	FVector m_hubPosition;

	void UpdateNodeData(const TArray<FQuat>& _nodeQuat, const TArray<FVector>& _nodeAccel);

	void UpdateHubRotation(const FQuat& _hubRotationRaw,
		const FQuat& _hubRotationOffset);

	void UpdateHubPosition(const FVector& _positionOffset);

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};