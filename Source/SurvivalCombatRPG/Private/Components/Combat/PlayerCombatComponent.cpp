// Copyright Ricky Everest


#include "Components/Combat/PlayerCombatComponent.h"

#include "Items/Weapons/SCR_PlayerWeaponBase.h"
#include "Net/UnrealNetwork.h"


ASCR_PlayerWeaponBase* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ASCR_PlayerWeaponBase>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

