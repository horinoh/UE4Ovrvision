// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UE4OvrvisionEditorTarget : TargetRules
{
	public UE4OvrvisionEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.Add("UE4Ovrvision");
	}
}
