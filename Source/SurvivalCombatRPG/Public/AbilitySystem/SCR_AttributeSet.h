// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SCR_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

// typedef is specific to the FGameplayAttribute() signature, but TStaticFunPtr is generic to any signature chosen
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USCR_AttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	

	//=========================================================================
	// Primary Attributes
	//=========================================================================
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Dexterity);

	// “Toughness” is now mapped as a primary attribute but its RepNotify function is named OnRep_Resilience.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Toughness;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Toughness);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Athletics, Category = "Primary Attributes")
	FGameplayAttributeData Athletics;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Athletics);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Perception, Category = "Primary Attributes")
	FGameplayAttributeData Perception;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Perception);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Soul, Category = "Primary Attributes")
	FGameplayAttributeData Soul;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Soul);




	/*
	 * Secondary Attributes
	 */
	
	  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeAttack, Category = "Secondary Attributes")
    FGameplayAttributeData MeleeAttack;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MeleeAttack);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeSpeed, Category = "Secondary Attributes")
    FGameplayAttributeData MeleeSpeed;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MeleeSpeed);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxCarryWeight, Category = "Secondary Attributes")
    FGameplayAttributeData MaxCarryWeight;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxCarryWeight);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stealth, Category = "Secondary Attributes")
    FGameplayAttributeData Stealth;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Stealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Armor);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
    FGameplayAttributeData ArmorPenetration;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, ArmorPenetration);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Secondary Attributes")
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Defense);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageResistance, Category = "Secondary Attributes")
    FGameplayAttributeData DamageResistance;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, DamageResistance);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicResistance, Category = "Secondary Attributes")
    FGameplayAttributeData MagicResistance;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MagicResistance);


    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegeneration, Category = "Secondary Attributes")
    FGameplayAttributeData StaminaRegeneration;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, StaminaRegeneration);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ProjectileAttackSpeed, Category = "Secondary Attributes")
    FGameplayAttributeData ProjectileAttackSpeed;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, ProjectileAttackSpeed);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ProjectileRange, Category = "Secondary Attributes")
    FGameplayAttributeData ProjectileRange;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, ProjectileRange);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Accuracy, Category = "Secondary Attributes")
    FGameplayAttributeData Accuracy;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Accuracy);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Concentration, Category = "Secondary Attributes")
    FGameplayAttributeData Concentration;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Concentration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, CriticalHitChance);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
    FGameplayAttributeData CriticalHitDamage;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, CriticalHitDamage);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
    FGameplayAttributeData CriticalHitResistance;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, CriticalHitResistance);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
    FGameplayAttributeData ManaRegeneration;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, ManaRegeneration);

	

	   //=========================================================================
    // Vital (Core) Attributes
    //=========================================================================

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Blood, Category = "Vital Attributes")
	FGameplayAttributeData Blood;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Blood);
	
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Mana);
	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Stamina);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Hunger, Category = "Vital Attributes")
	FGameplayAttributeData Hunger;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, Hunger);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HeadHealth, Category = "Vital Attributes")
	FGameplayAttributeData HeadHealth;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, HeadHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ChestHealth, Category = "Vital Attributes")
	FGameplayAttributeData ChestHealth;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, ChestHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StomachHealth, Category = "Vital Attributes")
	FGameplayAttributeData StomachHealth;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, StomachHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RightArmHealth, Category = "Vital Attributes")
	FGameplayAttributeData RightArmHealth;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, RightArmHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LeftArmHealth, Category = "Vital Attributes")
	FGameplayAttributeData LeftArmHealth;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, LeftArmHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RightLegHealth, Category = "Vital Attributes")
	FGameplayAttributeData RightLegHealth;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, RightLegHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LeftLegHealth, Category = "Vital Attributes")
	FGameplayAttributeData LeftLegHealth;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, LeftLegHealth);

	


    //=========================================================================
    // Vital (Extended) Attributes
    //=========================================================================
	// Note: MaxMana appears in the constructor mapping for Secondary.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxBlood, Category = "Secondary Attributes")
	FGameplayAttributeData MaxBlood;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxBlood);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Vital Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxStamina);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
    FGameplayAttributeData HealthRegeneration;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, HealthRegeneration);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BloodRegeneration, Category = "Secondary Attributes")
    FGameplayAttributeData BloodRegeneration;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, BloodRegeneration);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHunger, Category = "Secondary Attributes")
    FGameplayAttributeData MaxHunger;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxHunger);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHeadHealth, Category = "Secondary Attributes")
    FGameplayAttributeData MaxHeadHealth;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxHeadHealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxChestHealth, Category = "Secondary Attributes")
    FGameplayAttributeData MaxChestHealth;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxChestHealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStomachHealth, Category = "Secondary Attributes")
    FGameplayAttributeData MaxStomachHealth;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxStomachHealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxRightArmHealth, Category = "Secondary Attributes")
    FGameplayAttributeData MaxRightArmHealth;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxRightArmHealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxLeftArmHealth, Category = "Secondary Attributes")
    FGameplayAttributeData MaxLeftArmHealth;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxLeftArmHealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxRightLegHealth, Category = "Secondary Attributes")
    FGameplayAttributeData MaxRightLegHealth;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxRightLegHealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxLeftLegHealth, Category = "Secondary Attributes")
    FGameplayAttributeData MaxLeftLegHealth;
    ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxLeftLegHealth);

	
	/*
	 * Resistance Attributes
	 */
 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Resistance Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, FireResistance);
 	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Resistance Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, LightningResistance);
 	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneResistance, Category = "Resistance Attributes")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, ArcaneResistance);
 	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Resistance Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, PhysicalResistance);

	
	/*
	 * Meta Attributes
	 */
 
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, IncomingDamage);



	

	
 //=========================================================================
    // Replication Notification Functions
    //=========================================================================


	
	UFUNCTION()
	void OnRep_Blood(const FGameplayAttributeData& OldBlood) const;
	
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	
    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

    UFUNCTION()
    void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

    UFUNCTION()
    void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

    UFUNCTION()
    void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;

    UFUNCTION()
    void OnRep_Athletics(const FGameplayAttributeData& OldAthletics) const;

    UFUNCTION()
    void OnRep_Perception(const FGameplayAttributeData& OldPerception) const;

    UFUNCTION()
    void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

    UFUNCTION()
    void OnRep_Soul(const FGameplayAttributeData& OldSoul) const;

    UFUNCTION()
    void OnRep_MeleeAttack(const FGameplayAttributeData& OldMeleeAttack) const;

    UFUNCTION()
    void OnRep_MeleeSpeed(const FGameplayAttributeData& OldMeleeSpeed) const;

    UFUNCTION()
    void OnRep_MaxCarryWeight(const FGameplayAttributeData& OldMaxCarryWeight) const;

    UFUNCTION()
    void OnRep_Stealth(const FGameplayAttributeData& OldStealth) const;

    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

    UFUNCTION()
    void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

    UFUNCTION()
    void OnRep_Defense(const FGameplayAttributeData& OldDefense) const;

    UFUNCTION()
    void OnRep_DamageResistance(const FGameplayAttributeData& OldDamageResistance) const;

    UFUNCTION()
    void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;

    UFUNCTION()
    void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

    UFUNCTION()
    void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const;

    UFUNCTION()
    void OnRep_ProjectileAttackSpeed(const FGameplayAttributeData& OldProjectileAttackSpeed) const;

    UFUNCTION()
    void OnRep_ProjectileRange(const FGameplayAttributeData& OldProjectileRange) const;

    UFUNCTION()
    void OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy) const;

    UFUNCTION()
    void OnRep_Concentration(const FGameplayAttributeData& OldConcentration) const;

    UFUNCTION()
    void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

    UFUNCTION()
    void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

    UFUNCTION()
    void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

    UFUNCTION()
    void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

    UFUNCTION()
    void OnRep_MaxBlood(const FGameplayAttributeData& OldMaxBlood) const;

    UFUNCTION()
    void OnRep_BloodRegeneration(const FGameplayAttributeData& OldBloodRegeneration) const;

    UFUNCTION()
    void OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const;

    UFUNCTION()
    void OnRep_Hunger(const FGameplayAttributeData& OldHunger) const;

    UFUNCTION()
    void OnRep_MaxHeadHealth(const FGameplayAttributeData& OldMaxHeadHealth) const;

    UFUNCTION()
    void OnRep_MaxChestHealth(const FGameplayAttributeData& OldMaxChestHealth) const;

    UFUNCTION()
    void OnRep_MaxStomachHealth(const FGameplayAttributeData& OldMaxStomachHealth) const;

    UFUNCTION()
    void OnRep_MaxRightArmHealth(const FGameplayAttributeData& OldMaxRightArmHealth) const;

    UFUNCTION()
    void OnRep_MaxLeftArmHealth(const FGameplayAttributeData& OldMaxLeftArmHealth) const;

    UFUNCTION()
    void OnRep_MaxRightLegHealth(const FGameplayAttributeData& OldMaxRightLegHealth) const;

    UFUNCTION()
    void OnRep_MaxLeftLegHealth(const FGameplayAttributeData& OldMaxLeftLegHealth) const;

    UFUNCTION()
    void OnRep_HeadHealth(const FGameplayAttributeData& OldHeadHealth) const;

    UFUNCTION()
    void OnRep_ChestHealth(const FGameplayAttributeData& OldChestHealth) const;

    UFUNCTION()
    void OnRep_StomachHealth(const FGameplayAttributeData& OldStomachHealth) const;

    UFUNCTION()
    void OnRep_RightArmHealth(const FGameplayAttributeData& OldRightArmHealth) const;

    UFUNCTION()
    void OnRep_LeftArmHealth(const FGameplayAttributeData& OldLeftArmHealth) const;

    UFUNCTION()
    void OnRep_RightLegHealth(const FGameplayAttributeData& OldRightLegHealth) const;

    UFUNCTION()
    void OnRep_LeftLegHealth(const FGameplayAttributeData& OldLeftLegHealth) const;

	
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;
 
	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;
 
	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const;
 
	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;



	// Movement Functions Experiment
	UPROPERTY(BlueprintReadOnly, Category = "MovementSpeed", ReplicatedUsing = OnRep_MaxMovementSpeed)
	FGameplayAttributeData MaxMovementSpeed;
	ATTRIBUTE_ACCESSORS(USCR_AttributeSet, MaxMovementSpeed)
	
	UFUNCTION()
	virtual void OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed);

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bCriticalHit) const;
};

