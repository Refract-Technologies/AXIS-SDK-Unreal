// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <BoneContainer.h>

#include "Axis_RotateOffset.generated.h"

USTRUCT(BlueprintType)
struct FAxis_RotateOffset
{
    GENERATED_BODY()
public:
    uint8 BoneIndex {0};
public:
    
    UPROPERTY(EditAnywhere, Category = "AXIS")
        FBoneReference  Bone;  
};