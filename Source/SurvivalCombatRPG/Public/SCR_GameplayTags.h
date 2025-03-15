// Copyright Ricky Everest

#pragma once

#include "NativeGameplayTags.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"



/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

	
	
	//  Primary Attributes


	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Strength)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Dexterity)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Toughness)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Athletics)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Perception)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Intelligence)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Soul)

	// Secondary
	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MeleeAttack)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MeleeSpeed)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxCarryWeight)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Stealth)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Armor)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ArmorPenetration)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Defense)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_DamageResistance)
	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_StaminaRegeneration)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ProjectileAttackSpeed)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ProjectileRange)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Accuracy)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MagicResistance)
	 
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Concentration)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitDamage)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitChance)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitResistance)


	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ManaRegeneration)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxMana)
	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxBlood)
	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_HealthRegeneration)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_BloodRegeneration)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHunger)

	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxStamina)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHeadHealth)	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxChestHealth)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxStomachHealth)


	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxRightArmHealth)	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxLeftArmHealth)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxRightLegHealth)	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxLeftLegHealth)

	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Blood)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Stamina)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Mana)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_HeadHealth)	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_ChestHealth)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_StomachHealth)
 

	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_RightArmHealth)	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_LeftArmHealth)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_RightLegHealth)	
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_LeftLegHealth)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Hunger)

struct FSCR_GameplayTags
{
public:
	static const FSCR_GameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTagContainer SCR_TagsContainer = FGameplayTagContainer();

		FGameplayTag InputTag_LMB;
		FGameplayTag InputTag_RMB;
		FGameplayTag InputTag_1;
		FGameplayTag InputTag_2;
		FGameplayTag InputTag_3;
		FGameplayTag InputTag_4;

protected:

private:
	static FSCR_GameplayTags GameplayTags;
};
namespace SCR_GameplayTags
{
	/** Input Tags **/
	SURVIVALCOMBATRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	SURVIVALCOMBATRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	SURVIVALCOMBATRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump)

	/* UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LMB)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_RMB)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_1)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_2)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_3)
	 UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_4)*/

}
