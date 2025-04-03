// Copyright Ricky Everest


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystem/Abilities/SCR_EnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(USCR_AbilitySystemComponent* InASCToGive,
                                                               int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf < USCR_EnemyGameplayAbility >& AbilityClass : EnemyCombatAbilities)
		{
			if(!AbilityClass) continue;
 
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
 
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
