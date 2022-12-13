
#include "Axis_Animation_Graph_Node.h"
#include <Kismet2/CompilerResultsLog.h>
//#include "CompilerResultsLog.h"

#define LOCTEXT_NAMESPACE "FAxisEditor"
UAxis_Animation_Graph_Node::UAxis_Animation_Graph_Node(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
// Begin UEdGraphNode interface.
FLinearColor UAxis_Animation_Graph_Node::GetNodeTitleColor() const
{
	return FLinearColor::Black;
}
FText UAxis_Animation_Graph_Node::GetTooltipText()const
{
	return FText::FromString("If you this as the start node you have the pose given by AXIS Mannequin");
}
FText UAxis_Animation_Graph_Node::GetNodeTitle(ENodeTitleType::Type TitleType)const
{	
	return FText::FromString("AxisMannequinPose");
}
FString UAxis_Animation_Graph_Node::GetNodeCategory()const
{
	return TEXT("AXIS");
}
void UAxis_Animation_Graph_Node::PreloadRequiredAssets()
{

}
void UAxis_Animation_Graph_Node::ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog)
{
	//Unreal check
	// Temporary fix where skeleton is not fully loaded during AnimBP compilation and thus virtual bone name check is invalid UE-39499 (NEED FIX) 
	
	
	if (ForSkeleton && !ForSkeleton->HasAnyFlags(RF_NeedPostLoad))
	{
		const TMap<TEnumAsByte<EAxisPartEnum>, FAxis_RotateOffset>& _axismToRotation = Node.AxisMToRotation;
		for (const auto& pair : _axismToRotation)
		{
			const FBoneReference& currBone = pair.Value.Bone;
			if (ForSkeleton->GetReferenceSkeleton().FindBoneIndex(currBone.BoneName) == INDEX_NONE)
			{
				if (currBone.BoneName == NAME_None)
				{
					
					FFormatNamedArguments Args;
					Args.Add(TEXT("BoneName"), FText::FromName(currBone.BoneName));
					Args.Add(TEXT("Part"), FText::FromString(UEnum::GetValueAsString(pair.Key.GetValue())));
					
					FText Msg = FText::Format(LOCTEXT("NoneBoneFound", "@@ - Bone {BoneName} not found in Skeleton in {Part} Settings"), Args);
					
					MessageLog.Warning(*Msg.ToString(), this);
				}
					
			}
		}
	}

	Super::ValidateAnimNodeDuringCompilation(ForSkeleton, MessageLog);
}
void UAxis_Animation_Graph_Node::Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp) const
{
	
}

void UAxis_Animation_Graph_Node::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	
}
#undef LOCTEXT_NAMESPACE