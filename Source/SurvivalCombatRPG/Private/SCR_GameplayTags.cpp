// Copyright Ricky Everest

#include "SCR_GameplayTags.h"
#include "GameplayTagsManager.h"

//#define ADDNATIVETAG(AttributeType, AttributeName, Comment) \
//	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_##AttributeType##_##AttributeName, *FString((FString("Attributes.") + #AttributeType + FString(".")+#AttributeName)), Comment)

// Alternative Solution
#define ADDNATIVETAG(AttributeType, AttributeName, Comment) \
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_##AttributeType##_##AttributeName, *FString(FString("Attributes.") + #AttributeType + FString(".") + #AttributeName), Comment)

ADDNATIVETAG(Primary, Strength, "Increases physical Strength")
ADDNATIVETAG(Primary, Dexterity, "Increase Skill ")
ADDNATIVETAG(Primary, Toughness, "Damage Resistance and Knockout Resistance")
ADDNATIVETAG(Primary, Athletics, "Governs Running Speed and Stamina")
ADDNATIVETAG(Primary, Perception, "Governs Ranged Abilities and Awareness")
ADDNATIVETAG(Primary, Intelligence, "Mana Capacity and Resistance")
ADDNATIVETAG(Primary, Soul, "WildCard")


ADDNATIVETAG(Secondary, MeleeAttack, "Max Bonk Capacity")
ADDNATIVETAG(Secondary, MeleeSpeed, "Faster Swings")
ADDNATIVETAG(Secondary, MaxCarryWeight, "Carry Weight")
ADDNATIVETAG(Secondary, Stealth, "Ability To elude enemy perception")
ADDNATIVETAG(Secondary, Armor, "Total Armored Resistance")
ADDNATIVETAG(Secondary, ArmorPenetration, "Ability To Bypass Armor")
ADDNATIVETAG(Secondary, Defense, "Ability To Actively Ward Off Incoming Damage ")
ADDNATIVETAG(Secondary, DamageResistance, "Attacks Hurt Less")
ADDNATIVETAG(Secondary, MagicResistance, "DamageResistance but magical")

ADDNATIVETAG(Secondary, MaxStamina, "Modifies Max Stamina And Regeneration")
ADDNATIVETAG(Secondary, StaminaRegeneration, "How Quickly you Regenerate Stamina")
ADDNATIVETAG(Secondary, ProjectileAttackSpeed, "Draw and Reload Rate")
ADDNATIVETAG(Secondary, ProjectileRange,"Damage Falloff" )
ADDNATIVETAG(Secondary, Accuracy, "Reticle Size")
ADDNATIVETAG(Secondary, Concentration, "Wild Effect Resistance")

ADDNATIVETAG(Secondary, CriticalHitDamage, "CriticalHitDamage")
ADDNATIVETAG(Secondary, CriticalHitChance, "CriticalHitChance")
ADDNATIVETAG(Secondary, CriticalHitResistance, "CriticalHitResistance")
ADDNATIVETAG(Secondary, ManaRegeneration, "ManaRegeneration")
ADDNATIVETAG(Secondary, MaxMana, "MaxMana")


ADDNATIVETAG(Secondary, MaxBlood, "MaxBlood")
ADDNATIVETAG(Secondary, HealthRegeneration, "HealthRegeneration")
ADDNATIVETAG(Secondary, BloodRegeneration, "BloodRegeneration")
ADDNATIVETAG(Secondary, MaxHunger, "MaxHunger")
ADDNATIVETAG(Secondary, MaxHeadHealth, "MaxHeadHealth")
ADDNATIVETAG(Secondary, MaxChestHealth, "MaxChestHealth")
ADDNATIVETAG(Secondary, MaxStomachHealth, "MaxStomachHealth")
ADDNATIVETAG(Secondary, MaxRightArmHealth, "MaxRightArmHealth")
ADDNATIVETAG(Secondary, MaxLeftArmHealth, "MaxLeftArmHealth")
ADDNATIVETAG(Secondary, MaxRightLegHealth, "MaxRightLegHealth")
ADDNATIVETAG(Secondary, MaxLeftLegHealth, "MaxLeftLegHealth")

ADDNATIVETAG(Vital, Stamina, "Modifies Max Stamina And Regeneration")
ADDNATIVETAG(Vital, Blood, "Blood")
ADDNATIVETAG(Vital, Mana, "Blood")
ADDNATIVETAG(Vital, Hunger, "Hunger")
ADDNATIVETAG(Vital, HeadHealth, "HeadHealth")
ADDNATIVETAG(Vital, ChestHealth, "ChestHealth")
ADDNATIVETAG(Vital, StomachHealth, "StomachHealth")
ADDNATIVETAG(Vital, RightArmHealth, "RightArmHealth")
ADDNATIVETAG(Vital, LeftArmHealth, "LeftArmHealth")
ADDNATIVETAG(Vital, RightLegHealth, "RightLegHealth")
ADDNATIVETAG(Vital, LeftLegHealth, "LeftLegHealth")



namespace SCR_GameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move,"InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look,"InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump,"InputTag.Jump")
}



FSCR_GameplayTags FSCR_GameplayTags::GameplayTags;

void FSCR_GameplayTags::InitializeNativeGameplayTags()
{
#define ADDTAGTO_CONTAINER(AttributeType, AttributeName) GameplayTags.SCR_TagsContainer.AddTag(Attributes_##AttributeType##_##AttributeName);
/*
	 * Primary Attributes
	 */
	ADDTAGTO_CONTAINER(Primary, Strength)
	ADDTAGTO_CONTAINER(Primary, Dexterity)
	ADDTAGTO_CONTAINER(Primary, Toughness)
	ADDTAGTO_CONTAINER(Primary, Athletics)
	ADDTAGTO_CONTAINER(Primary, Perception)
	ADDTAGTO_CONTAINER(Primary, Intelligence)
	ADDTAGTO_CONTAINER(Primary, Soul)


	ADDTAGTO_CONTAINER(Secondary, MeleeAttack)
	ADDTAGTO_CONTAINER(Secondary, MeleeSpeed)
	ADDTAGTO_CONTAINER(Secondary, MaxCarryWeight)
	ADDTAGTO_CONTAINER(Secondary, Stealth)
	ADDTAGTO_CONTAINER(Secondary, Armor)
	ADDTAGTO_CONTAINER(Secondary, ArmorPenetration)
	ADDTAGTO_CONTAINER(Secondary, Defense)
	ADDTAGTO_CONTAINER(Secondary, DamageResistance)
	ADDTAGTO_CONTAINER(Secondary, MagicResistance)

	ADDTAGTO_CONTAINER(Secondary, MaxStamina)
	ADDTAGTO_CONTAINER(Secondary, StaminaRegeneration)
	ADDTAGTO_CONTAINER(Secondary, ProjectileAttackSpeed)
	ADDTAGTO_CONTAINER(Secondary, ProjectileRange)
	ADDTAGTO_CONTAINER(Secondary, Accuracy)
	ADDTAGTO_CONTAINER(Secondary, Concentration)

	ADDTAGTO_CONTAINER(Secondary, CriticalHitDamage)
	ADDTAGTO_CONTAINER(Secondary, CriticalHitChance)
	ADDTAGTO_CONTAINER(Secondary, CriticalHitResistance)
	ADDTAGTO_CONTAINER(Secondary, ManaRegeneration)
	ADDTAGTO_CONTAINER(Secondary, HealthRegeneration)
	ADDTAGTO_CONTAINER(Secondary, BloodRegeneration)

	ADDTAGTO_CONTAINER(Secondary, MaxMana)

	
	ADDTAGTO_CONTAINER(Secondary, MaxBlood)
	ADDTAGTO_CONTAINER(Secondary, MaxHunger)
	ADDTAGTO_CONTAINER(Secondary, MaxHeadHealth)
	ADDTAGTO_CONTAINER(Secondary, MaxChestHealth)
	ADDTAGTO_CONTAINER(Secondary, MaxStomachHealth)
	ADDTAGTO_CONTAINER(Secondary, MaxRightArmHealth)
	ADDTAGTO_CONTAINER(Secondary, MaxLeftArmHealth)
	ADDTAGTO_CONTAINER(Secondary, MaxRightLegHealth)
	ADDTAGTO_CONTAINER(Secondary, MaxLeftLegHealth)

	ADDTAGTO_CONTAINER(Vital, Blood)
	ADDTAGTO_CONTAINER(Vital, Hunger)
	ADDTAGTO_CONTAINER(Vital, Stamina)
	ADDTAGTO_CONTAINER(Vital, Mana)
	ADDTAGTO_CONTAINER(Vital, HeadHealth)
	ADDTAGTO_CONTAINER(Vital, ChestHealth)
	ADDTAGTO_CONTAINER(Vital, StomachHealth)
	ADDTAGTO_CONTAINER(Vital, RightArmHealth)
	ADDTAGTO_CONTAINER(Vital, LeftArmHealth)
	ADDTAGTO_CONTAINER(Vital, RightLegHealth)
	ADDTAGTO_CONTAINER(Vital, LeftLegHealth)
		

	/*
  * Input Tags
  */
 	
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);
 
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
		);
 
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);
 
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);
 
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);
 
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
		);
}
