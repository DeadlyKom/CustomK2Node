// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CustomK2Node : ModuleRules
{
	public CustomK2Node(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore"
            });
	}
}
