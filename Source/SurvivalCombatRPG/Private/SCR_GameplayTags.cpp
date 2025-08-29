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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch,"InputTag.Crouch")
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint")
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipSword, "InputTag.EquipSword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquipSword, "InputTag.UnEquipSword");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Sword,"InputTag.LightAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Sword,"InputTag.HeavyAttack.Sword");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll,"InputTag.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dodge,"InputTag.Dodge");

	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Test,"InputTag.Test");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword,"Player.Weapon.Sword");

	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Sword,"Player.Ability.Attack.Heavy.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Sword,"Player.Ability.Attack.Light.Sword");
	

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Sword, "Player.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UnEquip_Sword, "Player.Ability.UnEquip.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Test, "Player.Ability.Test");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll,"Player.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dodge,"Player.Ability.Dodge");
	
	UE_DEFINE_GAMEPLAY_TAG(Event_Weapon_Melee_EquipSword, "Event.Weapon.Melee.EquipSword");
	UE_DEFINE_GAMEPLAY_TAG(Event_Weapon_Melee_UnEquipSword, "Event.Weapon.Melee.UnEquipSword");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling,"Player.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dodge,"Player.Status.Dodge");

	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light,"Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy,"Player.SetByCaller.AttackType.Heavy");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause,"Player.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause,"Player.Event.HitPause");

	
	/** Player movement Ability Tags **/

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_InAir_Jump, "Player.Ability.InAir.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Movement_Crouch, "Player.Ability.Movement.Crouch");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Movement_Sprint, "Player.Ability.Movement.Sprint");

	/** Player movement State Tags **/
	UE_DEFINE_GAMEPLAY_TAG(State_InAir_Jumping, "State.InAir.Jumping");
	UE_DEFINE_GAMEPLAY_TAG(State_Movement_Crouch, "State.Movement.Crouch");
	
	UE_DEFINE_GAMEPLAY_TAG(State_Movement_Sprint,"State.Movement.Sprint");
	
	/** Player movement Event Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_Jump,"Event.Movement.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_OnStartCrouch, "Event.Movement.OnStartCrouch");
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_OnEndCrouch, "Event.Movement.OnEndCrouch");
	
	/** Enemy tags **/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon,"Enemy.Weapon");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing,"Enemy.Status.Strafing");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack,"Enemy.Status.UnderAttack");
	

	/** Abilities Enemy **/
	
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Attack,"Abilities.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Abilities_Melee,"Enemy.Abilities.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Abilities_Range,"Enemy.Abilities.Range");

	/** Shared tags **/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit,"Shared.Event.MeleeHit");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage,"Shared.SetByCaller.BaseDamage");


	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact,"Shared.Ability.HitReact");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact,"Shared.Event.HitReact");
	
	/** Input Events **/
	UE_DEFINE_GAMEPLAY_TAG(Input_Event_PrimaryAttack,"Input.Event.PrimaryAttack");
	UE_DEFINE_GAMEPLAY_TAG(Input_Event_SecondaryAttack,"Input.Event.SecondaryAttack");
	UE_DEFINE_GAMEPLAY_TAG(Input_Event_SpecialAttack,"Input.Event.SpecialAttack");
	
	//future death imp tags
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death,"Shared.Ability.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead,"Shared.Status.Dead");

	// Gore Tags UE Gore
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Character_DamageTaken,"GameplayCue.Character.DamageTaken");
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
	
	/** Player tags **/
	
 	
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
	


	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage"),
	FString("Damage")
	);

	
	/*
	  * Damage Types
	  */
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		 FName("Damage.Fire"),
		 FString("Fire Damage Type")
		 );
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		 FName("Damage.Lightning"),
		 FString("Lightning Damage Type")
		 );
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Arcane"),
		FString("Arcane Damage Type")
		);
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type")
		);
 
	/*
	 * Resistances
	 */
 
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"),
		FString("Resistance to Arcane damage")
		);
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("Resistance to Fire damage")
		);
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("Resistance to Lightning damage")
		);
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("Resistance to Physical damage")
		);
 
	/*
	 * Map of Damage Types to Resistances
	 */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
 
	/*
	 * Effects
	 */
	
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	 FName("Effects.HitReact"),
	 FString("Tag granted when Hit Reacting")
	 );
	
	/*
  * Montage
  */
 
	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Weapon"),
		FString("Weapon")
		);
 
	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.RightHand"),
		FString("Right Hand")
		);
 	
	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.LeftHand"),
		FString("Left Hand")
		);
	
	GameplayTags.Montage_Attack_LeftHand_Spell = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.LeftHand.Spell"),
	FString("Left Hand Spell")
	);

	
	// Montage.Attack.Grunt.Mace
	GameplayTags.Montage_Attack_Grunt_Mace = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Montage.Attack.Grunt.Mace"),
FString("Temp Grunt Mace Attack Tag")
);
	
	GameplayTags.Abilities_Arcane_ArcaneShards = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Arcane.ArcaneShards"),
	FString("Arcane Shards Ability Tag")
	);

	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Player.Block.InputPressed"),
FString("Block input pressed")
);


	
}
