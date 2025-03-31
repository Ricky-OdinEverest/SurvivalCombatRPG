// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h" // Contains FGameplayAbilityTargetData
#include "Items/Weapons/SCR_PlayerWeaponBase.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "SCR_AbilityTypes.generated.h"

class ASCR_PlayerWeaponBase;
class UPlayerCombatComponent;

USTRUCT(BlueprintType)
struct FGameplayAbilityTargetData_Weapon : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

public:
	// The weapon actor pointer
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Data")
	TObjectPtr<ASCR_PlayerWeaponBase> Weapon = nullptr;

	// The player combat component pointer
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Data")
	TObjectPtr<UPlayerCombatComponent> PCC = nullptr;

	// NetSerialize is required for replication support
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_Weapon::StaticStruct();
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("FGameplayAbilityTargetData_Weapon (Weapon: %s, PCC: %s)"),
							   *GetNameSafe(Weapon.Get()), *GetNameSafe(PCC.Get()));
	}

};

// Specialization for network serialization support
template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_Weapon> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_Weapon>
{
	enum
	{
		WithNetSerializer = true,
	};
};
