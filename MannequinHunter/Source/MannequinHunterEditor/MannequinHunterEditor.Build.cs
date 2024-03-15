// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MannequinHunterEditor : ModuleRules
{
	public MannequinHunterEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
	}
}
