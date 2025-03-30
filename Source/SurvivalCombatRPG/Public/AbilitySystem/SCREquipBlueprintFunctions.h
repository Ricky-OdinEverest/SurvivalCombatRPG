// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilitySystem/AbilityTasks/SCR_EquipAbilityTask.h" 
#include "SCREquipBlueprintFunctions.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCREquipBlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** 
	 * Returns the ASCR_PlayerWeaponBase stored in your custom FGameplayAbilityTargetData_Weapon.
	 * Returns nullptr if the handle is invalid or the data isn’t your custom struct.
	 */
	UFUNCTION(BlueprintPure, Category="Ability|TargetData")
	static class ASCR_PlayerWeaponBase* GetWeaponFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index = 0);

	/**
	 * Returns the UPlayerCombatComponent stored in your custom FGameplayAbilityTargetData_Weapon.
	 * Returns nullptr if the handle is invalid or the data isn’t your custom struct.
	 */
	UFUNCTION(BlueprintPure, Category="Ability|TargetData")
	static class UPlayerCombatComponent* GetCombatComponentFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index = 0);
};

