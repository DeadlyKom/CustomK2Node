// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CustomK2NodeEditor : ModuleRules
{
	public CustomK2NodeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "UnrealEd",
                "GraphEditor",
                "BlueprintGraph",
                "KismetCompiler"
            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "CustomK2Node"
            });

        PublicIncludePathModuleNames.AddRange(
            new string[] {
                "CustomK2Node"
            });
    }
}
