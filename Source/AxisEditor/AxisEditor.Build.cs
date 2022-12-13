// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AxisEditor : ModuleRules
{
	public AxisEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core", "CoreUObject", "Engine", "InputCore", "SlateCore", 
				"Axis",
				"AnimGraph","BlueprintGraph","UnrealEd" }
			);

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
