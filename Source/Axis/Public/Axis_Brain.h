#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h" 
#include "IAxisControlledComponentCommandInterface.h"
#include "Windows/MinWindows.h"
#include "AxisRuntimeHandler.h"
#include "IAxisEventHandler.h"
#include "FrancisListener.h"
#include "PlayerLocationResolver.h"
#include "AxisEventEnum.h"
#include <BoneContainer.h>
#include "Axis_Brain.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AXIS_API UAxis_Brain : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (UseComponentPicker,
		AllowedClasses = "Axis_Mannequin",
		DisallowedClasses = "PrimitiveComponent",AllowAnyActor))
		TArray<FComponentReference> m_mannequins;


	void UpdateMannequins();

	UAxis_Brain();
	virtual ~UAxis_Brain();
private:

	void InitializeOnPlay();

	std::unique_ptr<AxisRuntimeHandler> m_axisRuntime;
	std::unique_ptr<IAxisEventHandler> m_axisEventHandler;
	std::unique_ptr<IAxisControlledComponentCommandInterface> m_axisCommandInterface;

	TArray<FQuat> m_nodeQuat;
	TArray<FQuat> m_zeroOffsetQuat;
	TArray<FVector> m_nodeAcceleration;

	FQuat m_hubRotationRaw;
	FQuat m_hubRotationOffsetRaw;
	
	FVector m_hubPosition;


	FQuat m_hubRotation;

	TSharedPtr<FFrancisListener> m_francisListener;

	PlayerLocationResolver m_playerLocationResolver;

	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	UFUNCTION(BlueprintCallable, Category = "AXIS Brain")
		FQuat GetNodeQuatData(const EAxisPartEnum& _axisNode);

	UFUNCTION(BlueprintCallable, Category = "AXIS Brain")
		FVector GetNodeAccelerationData(const EAxisPartEnum& _axisNode);

	UFUNCTION(BlueprintCallable, Category = "AXIS Brain")
		FVector GetHubPosition();

	UFUNCTION(BlueprintCallable, Category = "AXIS Brain")
		FQuat GetHubRotation();


	UFUNCTION(BlueprintCallable, Category = "AXIS Brain", Meta = (ExpandEnumAsExecs = "_eventEnum"))
		bool IsESPConnected(EEventEnum& _eventEnum, const float _timeout = 0.2f);

	UFUNCTION(BlueprintCallable, Category = "AXIS Brain", Meta = (ExpandEnumAsExecs = "_eventEnum"))
		bool IsHubConnected(EEventEnum& _eventEnum, const float _timeout = 0.2f);

	UFUNCTION(BlueprintCallable, Category = "AXIS Brain", Meta = (ExpandEnumAsExecs = "_eventEnum"))
		bool IsRuntimeConnected(EEventEnum& _eventEnum, const float _timeout = 0.2f);

	UFUNCTION(BlueprintCallable, Category = "AXIS Commands")
		bool CalibrateNodes();

	UFUNCTION(BlueprintCallable, Category = "AXIS Commands")
		bool ZeroNodes();
	
	UFUNCTION(blueprintCallable, Category = "AXIS Commands")
		bool ResetHub();



};