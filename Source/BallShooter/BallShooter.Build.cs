// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BallShooter : ModuleRules
{
	public BallShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
			"NavigationSystem",
		});
		
		PublicIncludePaths.AddRange(new string[]
		{
			"BallShooter/Public/Character",
		});
	}
}
