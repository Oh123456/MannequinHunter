// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OJKFramework : ModuleRules
{
	public OJKFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "OJKUtility", "Niagara" });
	}
}
