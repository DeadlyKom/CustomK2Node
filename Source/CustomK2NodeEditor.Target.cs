// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CustomK2NodeEditorTarget : TargetRules
{
	public CustomK2NodeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange(
            new string[] {
                "CustomK2Node",
                "CustomK2NodeEditor"
            });
    }
}
