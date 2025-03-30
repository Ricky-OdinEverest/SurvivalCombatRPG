// Copyright Ricky Everest


#include "Components/Combat/PlayerCombatComponent.h"

#include "Items/Weapons/SCR_PlayerWeaponBase.h"

ASCR_PlayerWeaponBase* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ASCR_PlayerWeaponBase>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
