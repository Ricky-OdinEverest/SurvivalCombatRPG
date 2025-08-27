// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SurvivalCombatRPG : ModuleRules
{
	public SurvivalCombatRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayTags",
			"GameplayTasks",
			"GameplayAbilities",
			"AIModule",
			"NetCore",
			"UMG",
			"AnimGraphRuntime",
			"MotionWarping"
			// Mods After Specified in Ninja Bear Docs
			/*"CommonUI",
			"ModelViewViewModel",
			"NinjaCombat",
			"NinjaCombatCamera",
			"NinjaCombatCore",
			"NinjaCombatActorPool",
			"NinjaCombatUI",
			"StructUtils",
			"UMG"*/
		});

		PrivateDependencyModuleNames.AddRange(new string[] {"NavigationSystem", "Niagara", "PCG" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
