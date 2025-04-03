// Copyright Ricky Everest


#include "AbilitySystem/Abilities/SCR_EnemyGameplayAbility.h"

#include "Characters/Enemy/SCR_Enemy.h"
#include "Components/Combat/SCR_EnemyCombatComponent.h"

ASCR_Enemy* USCR_EnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedSCREnemyCharacter.IsValid())
	{
		CachedSCREnemyCharacter = Cast<ASCR_Enemy>(CurrentActorInfo->AvatarActor);
	}
 
	return CachedSCREnemyCharacter.IsValid()? CachedSCREnemyCharacter.Get() : nullptr;
}

USCR_EnemyCombatComponent* USCR_EnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

