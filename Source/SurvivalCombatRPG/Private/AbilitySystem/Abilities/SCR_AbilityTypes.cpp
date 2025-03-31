// Copyright Ricky Everest


#include "AbilitySystem/Abilities/SCR_AbilityTypes.h"

#include "Items/Weapons/SCR_PlayerWeaponBase.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "Serialization/Archive.h"
#include "Engine/PackageMapClient.h"

bool FGameplayAbilityTargetData_Weapon::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Weapon;
	Ar << PCC;
	bOutSuccess = true;
	return true;
}