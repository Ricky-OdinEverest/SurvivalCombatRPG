// Copyright Ricky Everest


#include "Items/Weapons/SCR_PlayerWeaponBase.h"

#include "Net/UnrealNetwork.h"

ASCR_PlayerWeaponBase::ASCR_PlayerWeaponBase()
{
	bReplicates = true;
	AActor::SetReplicateMovement(true);
}

void ASCR_PlayerWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ASCR_PlayerWeaponBase, PlayerWeaponData);
}

void ASCR_PlayerWeaponBase::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> ASCR_PlayerWeaponBase::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
