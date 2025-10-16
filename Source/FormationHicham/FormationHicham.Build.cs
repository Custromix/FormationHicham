// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FormationHicham : ModuleRules
{
	public FormationHicham(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"UMG", 
			"AIModule", 
			"GameplayTasks", 
			"NavigationSystem"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate", "SlateCore"   // utiles pour UMG, gardés en Private tant que tu n'exposes pas de types Slate en .h
		});
	}
}
