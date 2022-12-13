// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include <CoreMinimal.h>



// The order is important as this is mapped to Axis Control Center
UENUM(BlueprintType)
enum EAxisPartEnum
{
	//0-15 are for nodes 16 is for hub
	THIGH_R = 0,
	CALF_R,
	THIGH_L,
	CALF_L,
	UPPERARM_R,
	LOWERARM_R,
	UPPERARM_L,
	LOWERARM_L,
	HEAD = 8,

	HUB
};

//What the Node is use for
UENUM(BlueprintType)
enum EAxisNodeUsageEnum
{
	//0-15 are for nodes 16 is for hub
	THIGH_R_NODE = 0,
	CALF_R_NODE,
	THIGH_L_NODE,
	CALF_L_NODE,
	UPPERARM_R_NODE,
	LOWERARM_R_NODE,
	UPPERARM_L_NODE,
	LOWERARM_L_NODE,
	HEAD_NODE,

	HUB_NODE,
	FREENODE
};

