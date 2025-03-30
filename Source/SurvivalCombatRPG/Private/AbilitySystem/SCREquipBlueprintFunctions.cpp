// Copyright Ricky Everest


#include "AbilitySystem/SCREquipBlueprintFunctions.h"
#include "AbilitySystem/AbilityTasks/SCR_EquipAbilityTask.h" 
#include "Items/Weapons/SCR_PlayerWeaponBase.h"
#include "Components/Combat/PlayerCombatComponent.h"

ASCR_PlayerWeaponBase* USCREquipBlueprintFunctions::GetWeaponFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index)
{
	// Validate the index and make sure there is data
	if (!TargetData.IsValid(Index))
	{
		return nullptr;
	}

	// Get the raw pointer to the target data
	const FGameplayAbilityTargetData* GenericData = TargetData.Get(Index);
	// Cast it to your custom struct
	const FGameplayAbilityTargetData_Weapon* MyData = static_cast<const FGameplayAbilityTargetData_Weapon*>(GenericData);
	if (!MyData)
	{
		return nullptr;
	}

	// Return the stored weapon pointer
	return MyData->Weapon.Get();
}

UPlayerCombatComponent* USCREquipBlueprintFunctions::GetCombatComponentFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index)
{
	if (!TargetData.IsValid(Index))
	{
		return nullptr;
	}

	const FGameplayAbilityTargetData* GenericData = TargetData.Get(Index);
	const FGameplayAbilityTargetData_Weapon* MyData = static_cast<const FGameplayAbilityTargetData_Weapon*>(GenericData);
	if (!MyData)
	{
		return nullptr;
	}

	return MyData->PCC.Get();
}