// Copyright Ricky Everest


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SCR_GameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(USCR_AbilitySystemComponent* InASCToGive,
                                                              int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities,InASCToGive,ApplyLevel);
	GrantAbilities(ReactiveAbilities,InASCToGive,ApplyLevel); 
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<USCR_GameplayAbility>>& InAbilitiesToGive,
	USCR_AbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{

	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<USCR_GameplayAbility>& Ability : InAbilitiesToGive)
	{
		if(!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
