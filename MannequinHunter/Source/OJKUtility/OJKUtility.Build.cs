// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OJKUtility : ModuleRules
{
	public OJKUtility(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
