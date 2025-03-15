// Copyright Ricky Everest


#include "AbilitySystem/SCR_AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "SCR_GameplayTags.h"

#include "Net/UnrealNetwork.h"

USCR_AttributeSet::USCR_AttributeSet()
{
	
	//const FSCR_GameplayTags& GameplayTags = FSCR_GameplayTags::Get();
#define MAPTAGSTOATTRIBUTES(AttributeType, AttributeName) \
		TagsToAttributes.Add(Attributes_##AttributeType##_##AttributeName, Get##AttributeName##Attribute);
	
	/* Primary Attributes */
	MAPTAGSTOATTRIBUTES(Primary, Strength)
	MAPTAGSTOATTRIBUTES(Primary, Dexterity)
	MAPTAGSTOATTRIBUTES(Primary, Toughness)
	MAPTAGSTOATTRIBUTES(Primary, Athletics)
	MAPTAGSTOATTRIBUTES(Primary, Perception)
	MAPTAGSTOATTRIBUTES(Primary, Intelligence)
	MAPTAGSTOATTRIBUTES(Primary, Soul)

	/* Secondary Attributes */
	MAPTAGSTOATTRIBUTES(Secondary, MeleeAttack)
	MAPTAGSTOATTRIBUTES(Secondary, MeleeSpeed)
	MAPTAGSTOATTRIBUTES(Secondary, MaxCarryWeight)
	MAPTAGSTOATTRIBUTES(Secondary, Stealth)
	MAPTAGSTOATTRIBUTES(Secondary, Armor)
	MAPTAGSTOATTRIBUTES(Secondary, ArmorPenetration)
	MAPTAGSTOATTRIBUTES(Secondary, Defense)
	MAPTAGSTOATTRIBUTES(Secondary, DamageResistance)
	MAPTAGSTOATTRIBUTES(Secondary, MagicResistance)

	MAPTAGSTOATTRIBUTES(Secondary, MaxStamina)
	MAPTAGSTOATTRIBUTES(Secondary, StaminaRegeneration)
	MAPTAGSTOATTRIBUTES(Secondary, ProjectileAttackSpeed)
	MAPTAGSTOATTRIBUTES(Secondary, ProjectileRange)
	MAPTAGSTOATTRIBUTES(Secondary, Accuracy)
	MAPTAGSTOATTRIBUTES(Secondary, Concentration)

	MAPTAGSTOATTRIBUTES(Secondary, CriticalHitChance)
	MAPTAGSTOATTRIBUTES(Secondary, CriticalHitDamage)
	MAPTAGSTOATTRIBUTES(Secondary, CriticalHitResistance)
	MAPTAGSTOATTRIBUTES(Secondary, ManaRegeneration)
	MAPTAGSTOATTRIBUTES(Secondary, MaxMana)
	
//Vital Secondary

	MAPTAGSTOATTRIBUTES(Secondary, MaxBlood)
	MAPTAGSTOATTRIBUTES(Secondary, HealthRegeneration)
	MAPTAGSTOATTRIBUTES(Secondary, BloodRegeneration)
	MAPTAGSTOATTRIBUTES(Secondary, MaxHunger)
	MAPTAGSTOATTRIBUTES(Secondary, MaxHeadHealth)
	MAPTAGSTOATTRIBUTES(Secondary, MaxChestHealth)
	MAPTAGSTOATTRIBUTES(Secondary, MaxStomachHealth)
	MAPTAGSTOATTRIBUTES(Secondary, MaxRightArmHealth)
	MAPTAGSTOATTRIBUTES(Secondary, MaxLeftArmHealth)
	MAPTAGSTOATTRIBUTES(Secondary, MaxRightLegHealth)
	MAPTAGSTOATTRIBUTES(Secondary, MaxLeftLegHealth)

	/* Vital Attributes */
	MAPTAGSTOATTRIBUTES(Vital, Stamina)
	MAPTAGSTOATTRIBUTES(Vital, Blood)
	MAPTAGSTOATTRIBUTES(Vital, Hunger)
	MAPTAGSTOATTRIBUTES(Vital, HeadHealth)
	MAPTAGSTOATTRIBUTES(Vital, ChestHealth)
	MAPTAGSTOATTRIBUTES(Vital, StomachHealth)
	MAPTAGSTOATTRIBUTES(Vital, RightArmHealth)
	MAPTAGSTOATTRIBUTES(Vital, LeftArmHealth)
	MAPTAGSTOATTRIBUTES(Vital, RightLegHealth)
	MAPTAGSTOATTRIBUTES(Vital, LeftLegHealth)
#undef MAPTAGSTOATTRIBUTES
}


void USCR_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Toughness, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Athletics, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Perception, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Soul, COND_None, REPNOTIFY_Always);




	// Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MeleeAttack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MeleeSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxCarryWeight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Stealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, DamageResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, StaminaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, ProjectileAttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, ProjectileRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Accuracy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Concentration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	
	// Vital Attributes
	
	
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Blood, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxBlood, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
		

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, BloodRegeneration, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxHunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, Hunger, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxHeadHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxChestHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxStomachHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxRightArmHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxLeftArmHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxRightLegHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, MaxLeftLegHealth, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, HeadHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, ChestHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, StomachHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, RightArmHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, LeftArmHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, RightLegHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCR_AttributeSet, LeftLegHealth, COND_None, REPNOTIFY_Always);





}

void USCR_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetBloodAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxBlood());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void USCR_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	if (Data.EvaluatedData.Attribute == GetBloodAttribute())
	{
		SetBlood(FMath::Clamp(GetBlood(), 0.f, GetMaxBlood()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Blood on %s, Blood: %f"), *Props.TargetAvatarActor->GetName(), GetBlood());
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void USCR_AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn()); 
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor); 
	}
}



void USCR_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Mana, OldMana);
}

void USCR_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxMana, OldMaxMana);
}

void USCR_AttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Strength, OldStrength);
}

void USCR_AttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Intelligence, OldIntelligence);
}

void USCR_AttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Toughness, OldResilience);
}


void USCR_AttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Armor, OldArmor);
}

void USCR_AttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, ArmorPenetration, OldArmorPenetration);
}

void USCR_AttributeSet::OnRep_Blood(const FGameplayAttributeData& OldBlood) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Blood, OldBlood);
}

void USCR_AttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Dexterity, OldDexterity);
}

void USCR_AttributeSet::OnRep_Athletics(const FGameplayAttributeData& OldAthletics) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Athletics, OldAthletics);
}

void USCR_AttributeSet::OnRep_Perception(const FGameplayAttributeData& OldPerception) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Perception, OldPerception);
}

void USCR_AttributeSet::OnRep_Soul(const FGameplayAttributeData& OldSoul) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Soul, OldSoul);
}

void USCR_AttributeSet::OnRep_MeleeAttack(const FGameplayAttributeData& OldMeleeAttack) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MeleeAttack, OldMeleeAttack);
}

void USCR_AttributeSet::OnRep_MeleeSpeed(const FGameplayAttributeData& OldMeleeSpeed) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MeleeSpeed, OldMeleeSpeed);
}

void USCR_AttributeSet::OnRep_MaxCarryWeight(const FGameplayAttributeData& OldMaxCarryWeight) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxCarryWeight, OldMaxCarryWeight);
}

void USCR_AttributeSet::OnRep_Stealth(const FGameplayAttributeData& OldStealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Stealth, OldStealth);
}

void USCR_AttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Defense, OldDefense);
}

void USCR_AttributeSet::OnRep_DamageResistance(const FGameplayAttributeData& OldDamageResistance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, DamageResistance, OldDamageResistance);
}

void USCR_AttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MagicResistance, OldMagicResistance);
}

void USCR_AttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Stamina, OldStamina);
}

void USCR_AttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxStamina, OldMaxStamina);
}

void USCR_AttributeSet::OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, StaminaRegeneration, OldStaminaRegeneration);
}

void USCR_AttributeSet::OnRep_ProjectileAttackSpeed(const FGameplayAttributeData& OldProjectileAttackSpeed) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, ProjectileAttackSpeed, OldProjectileAttackSpeed);
}

void USCR_AttributeSet::OnRep_ProjectileRange(const FGameplayAttributeData& OldProjectileRange) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, ProjectileRange, OldProjectileRange);
}

void USCR_AttributeSet::OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Accuracy, OldAccuracy);
}

void USCR_AttributeSet::OnRep_Concentration(const FGameplayAttributeData& OldConcentration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Concentration, OldConcentration);
}

void USCR_AttributeSet::OnRep_MaxBlood(const FGameplayAttributeData& OldMaxBlood) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxBlood, OldMaxBlood);
}

void USCR_AttributeSet::OnRep_BloodRegeneration(const FGameplayAttributeData& OldBloodRegeneration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, BloodRegeneration, OldBloodRegeneration);
}

void USCR_AttributeSet::OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxHunger, OldMaxHunger);
}

void USCR_AttributeSet::OnRep_Hunger(const FGameplayAttributeData& OldHunger) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, Hunger, OldHunger);
}

void USCR_AttributeSet::OnRep_MaxHeadHealth(const FGameplayAttributeData& OldMaxHeadHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxHeadHealth, OldMaxHeadHealth);
}

void USCR_AttributeSet::OnRep_MaxChestHealth(const FGameplayAttributeData& OldMaxChestHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxChestHealth, OldMaxChestHealth);
}

void USCR_AttributeSet::OnRep_MaxStomachHealth(const FGameplayAttributeData& OldMaxStomachHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxStomachHealth, OldMaxStomachHealth);
}

void USCR_AttributeSet::OnRep_MaxRightArmHealth(const FGameplayAttributeData& OldMaxRightArmHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxRightArmHealth, OldMaxRightArmHealth);
}

void USCR_AttributeSet::OnRep_MaxLeftArmHealth(const FGameplayAttributeData& OldMaxLeftArmHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxLeftArmHealth, OldMaxLeftArmHealth);
}

void USCR_AttributeSet::OnRep_MaxRightLegHealth(const FGameplayAttributeData& OldMaxRightLegHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxRightLegHealth, OldMaxRightLegHealth);
}

void USCR_AttributeSet::OnRep_MaxLeftLegHealth(const FGameplayAttributeData& OldMaxLeftLegHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, MaxLeftLegHealth, OldMaxLeftLegHealth);
}

void USCR_AttributeSet::OnRep_HeadHealth(const FGameplayAttributeData& OldHeadHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, HeadHealth, OldHeadHealth);
}

void USCR_AttributeSet::OnRep_ChestHealth(const FGameplayAttributeData& OldChestHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, ChestHealth, OldChestHealth);
}

void USCR_AttributeSet::OnRep_StomachHealth(const FGameplayAttributeData& OldStomachHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, StomachHealth, OldStomachHealth);
}

void USCR_AttributeSet::OnRep_RightArmHealth(const FGameplayAttributeData& OldRightArmHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, RightArmHealth, OldRightArmHealth);
}

void USCR_AttributeSet::OnRep_LeftArmHealth(const FGameplayAttributeData& OldLeftArmHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, LeftArmHealth, OldLeftArmHealth);
}

void USCR_AttributeSet::OnRep_RightLegHealth(const FGameplayAttributeData& OldRightLegHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, RightLegHealth, OldRightLegHealth);
}

void USCR_AttributeSet::OnRep_LeftLegHealth(const FGameplayAttributeData& OldLeftLegHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, LeftLegHealth, OldLeftLegHealth);
}

void USCR_AttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void USCR_AttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void USCR_AttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void USCR_AttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void USCR_AttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USCR_AttributeSet, ManaRegeneration, OldManaRegeneration);
}
