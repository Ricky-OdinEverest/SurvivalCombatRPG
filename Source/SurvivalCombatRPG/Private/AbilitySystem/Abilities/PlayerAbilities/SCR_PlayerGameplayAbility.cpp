// Copyright Ricky Everest


#include "AbilitySystem/Abilities/PlayerAbilities/SCR_PlayerGameplayAbility.h"

#include "Characters/Player/SCR_PlayerCharacter.h"
#include "Controllers/SCR_PlayerController.h"


ASCR_PlayerCharacter* USCR_PlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedSCRPlayerCharacter.IsValid())
	{
		CachedSCRPlayerCharacter = Cast<ASCR_PlayerCharacter>(CurrentActorInfo->AvatarActor);
	}
    
	return CachedSCRPlayerCharacter.IsValid()? CachedSCRPlayerCharacter.Get() : nullptr;
}

ASCR_PlayerController* USCR_PlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedSCRPlayerController.IsValid())
	{
		CachedSCRPlayerController = Cast<ASCR_PlayerController>(CurrentActorInfo->PlayerController);
	}
 
	return CachedSCRPlayerController.IsValid()? CachedSCRPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* USCR_PlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}
