// Copyright Ricky Everest


#include "DataAssets/StartUpData/DataAsset_PlayerStartUpData.h"

#include "AbilitySystem/Abilities/SCR_GameplayAbility.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"

void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(USCR_AbilitySystemComponent* InASCToGive,
                                                                int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FSCR_PlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if(!AbilitySet.IsValid()) continue;
 
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
 
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
