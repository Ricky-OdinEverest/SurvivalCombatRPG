// Copyright Ricky Everest


#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "SCR_GameplayTags.h"
#include "AbilitySystem/Abilities/SRC_GameplayAbility.h"

void USCR_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USCR_AbilitySystemComponent::ClientEffectApplied);

	const FSCR_GameplayTags& GameplayTags = FSCR_GameplayTags::Get();
}

void USCR_AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const USRC_GameplayAbility* SCR_Ability = Cast<USRC_GameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(SCR_Ability->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void USCR_AbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	
	if (!InputTag.IsValid()) return;
 
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}

}


void USCR_AbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{

	if (!InputTag.IsValid()) return;
 
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}

}

void USCR_AbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

}
