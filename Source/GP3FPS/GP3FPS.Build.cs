// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GP3FPS : ModuleRules
{
	public GP3FPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
