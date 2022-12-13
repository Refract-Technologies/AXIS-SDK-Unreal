// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Containers/EnumAsByte.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "Axis_RotateOffset.h"
#include "Axis_Mannequin.h"
#include "Axis_Enums.h"
#include "Axis_Animation_Node.generated.h"

USTRUCT(BlueprintType)
struct AXIS_API FAxis_Animation_Node : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
		FPoseLink BasePose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		TMap<TEnumAsByte<EAxisPartEnum>, FAxis_RotateOffset> AxisMToRotation;

public:
	FAxis_Animation_Node();
	virtual ~FAxis_Animation_Node() override;



	// FAnimNode_Base interface
#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION < 17)
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones(const FAnimationCacheBonesContext& Context) override;
	virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
#else
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
#endif
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;

private:
	TArray<FQuat> PoseWorldPositionOfRelevantNodes;
protected:
	TWeakObjectPtr<UAxis_Mannequin> m_mannequin;

};
