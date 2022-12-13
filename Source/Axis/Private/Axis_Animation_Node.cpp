// Fill out your copyright notice in the Description page of Project Settings.


#include "Axis_Animation_Node.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimTrace.h"
#include "Math/BigInt.h"
#include <GameFramework/InputSettings.h>
#include <string>
#include <sstream> 
#include "AxisHelper.h"

// Sets default values for this component's properties
FAxis_Animation_Node::FAxis_Animation_Node()
{
}
FAxis_Animation_Node::~FAxis_Animation_Node()
{
	
}
void FAxis_Animation_Node::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Initialize_AnyThread)
	FAnimNode_Base::Initialize_AnyThread(Context);
	UAnimInstance* fInstance = static_cast<UAnimInstance*>(Context.AnimInstanceProxy->GetAnimInstanceObject());

	m_mannequin = static_cast<UAxis_Mannequin*>(fInstance->GetOwningActor()->GetComponentByClass(UAxis_Mannequin::StaticClass()));
	
	USkeleton* skellie = Context.AnimInstanceProxy->GetSkeleton();
	USkeletalMeshComponent* meshComponent = Context.AnimInstanceProxy->GetSkelMeshComponent();
	FReferenceSkeleton refSkellie = skellie->GetReferenceSkeleton();
	BasePose.Initialize(Context);
	TArray<TEnumAsByte<EAxisPartEnum>> AxisPartEnum;
	AxisMToRotation.GetKeys(AxisPartEnum);

	for (int i = 0; i < AxisPartEnum.Num(); i++)
	{
		TEnumAsByte<EAxisPartEnum> AxisPartByte = AxisPartEnum[i];
		if(AxisMToRotation[AxisPartByte].Bone.BoneName != NAME_None)
			AxisMToRotation[AxisPartByte].BoneIndex = meshComponent->GetBoneIndex(AxisMToRotation[AxisPartByte].Bone.BoneName);
		
	}

}

inline FTransform GetLocalToWorldTransform(const FPoseContext& inCompatPose, FCompactPoseBoneIndex inBoneIndex)
{
	FTransform outTransform = FTransform::Identity;
	FTransform internalTrans = FTransform::Identity;
	if (inBoneIndex.IsRootBone())
		return outTransform;
	
	while (!inBoneIndex.IsRootBone())
	{
		inBoneIndex = inCompatPose.Pose.GetParentBoneIndex(inBoneIndex);
		internalTrans = inCompatPose.Pose[inBoneIndex];
		outTransform = outTransform * internalTrans;
	}
	return outTransform;

}
void FAxis_Animation_Node::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(CacheBones_AnyThread)
	BasePose.CacheBones(Context);
}
void FAxis_Animation_Node::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Update_AnyThread)
	GetEvaluateGraphExposedInputs().Execute(Context);

	BasePose.Update(Context);
}
void FAxis_Animation_Node::Evaluate_AnyThread(FPoseContext& Output)
{
 	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Evaluate_AnyThread)
	BasePose.Evaluate(Output);
	
	if (!Output.ContainsNaN())
	{
		//if(AXISController!=nullptr)
		if(m_mannequin != nullptr)
		{ 
			if (AxisMToRotation.Num() >= 1)
			{
				if (m_mannequin->m_nodeQuat.Num() >= 1)
				{
					TArray<TEnumAsByte<EAxisPartEnum>> AxisPartEnum;
					AxisMToRotation.GetKeys(AxisPartEnum);
					Output.ResetToRefPose();

					bool shouldPopulateWorldPosition = PoseWorldPositionOfRelevantNodes.Num() == 0;
					for (int i = 0; i < AxisPartEnum.Num(); i++)
					{
						TEnumAsByte<EAxisPartEnum> AxisPartByte = AxisPartEnum[i];
						//FOR ALL AXIS MANNEQUIN JOINT NODE
						int AxisPart = AxisPartByte;
						FAxis_RotateOffset offsetToFollow = AxisMToRotation[AxisPartByte];
						//For all nodes there are enums to use 
						uint8 UnrealBoneID = offsetToFollow.BoneIndex;
						//WHAT BONE TO DRIVE
						FCompactPoseBoneIndex BoneToMove{ UnrealBoneID };

						//getting the world transform of the reference bone once
						//probably need to find a better way
						if (shouldPopulateWorldPosition)
						{
							FTransform orilocalToWorldMatrix = GetLocalToWorldTransform(Output, BoneToMove);
							FTransform originalWorldSpaceOfBone = (Output.Pose.GetRefPose(BoneToMove) * orilocalToWorldMatrix);
							//current bone world matrix
							PoseWorldPositionOfRelevantNodes.Add(originalWorldSpaceOfBone.GetRotation());
						}

						//SET THE UNREAL BONE'S ROTATION TO THE AXIS PART ASSIGNED TO IT.
						
						FQuat axisCurrentRot = FQuat::Identity;
						if (AxisPart != EAxisPartEnum::HUB)
							axisCurrentRot = m_mannequin->m_nodeQuat[AxisPart];
						else
							axisCurrentRot = m_mannequin->m_hubRotationRaw;
							  
						//parent world matrix
						FTransform newLocalToWorldMatrix = GetLocalToWorldTransform(Output, BoneToMove);

						auto axisCorrectionRot = AxisHelper::DoAxisNodeCorrection(AxisPartByte, axisCurrentRot);

						Output.Pose[BoneToMove].SetRotation(newLocalToWorldMatrix.Inverse().GetRotation() * axisCorrectionRot * PoseWorldPositionOfRelevantNodes[i]);

						Output.Pose[BoneToMove].NormalizeRotation();
					}
				}
			}
		}
		else
		{
			UAnimInstance* fInstance = static_cast<UAnimInstance*>(Output.AnimInstanceProxy->GetAnimInstanceObject());
			
			m_mannequin = static_cast<UAxis_Mannequin*>(fInstance->GetOwningActor()->GetComponentByClass(UAxis_Mannequin::StaticClass()));
		}
	}
}
	

void FAxis_Animation_Node::GatherDebugData(FNodeDebugData& DebugData)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(GatherDebugData)
	FString DebugLine = DebugData.GetNodeName(this);
}
