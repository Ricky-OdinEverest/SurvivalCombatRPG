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
