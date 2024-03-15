// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MannequinHunterEditorTarget : TargetRules
{
	public MannequinHunterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("MannequinHunter");
        ExtraModuleNames.Add("OJKUtility");
        ExtraModuleNames.Add("OJKFramework");
        ExtraModuleNames.Add("MannequinHunterEditor");
    }
}
