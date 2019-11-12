// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CustomK2NodeTarget : TargetRules
{
	public CustomK2NodeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange(
            new string[] {
                "CustomK2Node"
            });
	}
}
