// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Axis_Animation_Node.h"
#include "AnimGraphNode_Base.h"
#include "Axis_Animation_Node.h"
#include "Axis_Animation_Graph_Node.generated.h"

//UCLASS(MinimalAPI)
UCLASS(BlueprintType)
class AXISEDITOR_API UAxis_Animation_Graph_Node : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "AXIS")
		FAxis_Animation_Node Node;
	// Begin UEdGraphNode interface.
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	// End UEdGraphNode interface.

	// UAnimGraphNode_Base interface
	virtual FString GetNodeCategory() const override;
	virtual void PreloadRequiredAssets() override;

	virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;
	virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp) const override;

};
