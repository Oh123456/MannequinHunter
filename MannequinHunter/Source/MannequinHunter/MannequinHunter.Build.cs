// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MannequinHunter : ModuleRules
{
	public MannequinHunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" , "OJKFramework", "OJKUtility", "AIModule", "GameplayTasks" , "MannequinHunterEditor", "UMG" });
    }
}
