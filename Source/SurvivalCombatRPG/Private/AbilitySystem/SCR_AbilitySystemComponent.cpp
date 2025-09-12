// Copyright Ricky Everest


#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "SCR_GameplayTags.h"
#include "AbilitySystem/Abilities/SCR_GameplayAbility.h"
#include "PlayerTypes/PlayerStructTypes.h"

void USCR_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USCR_AbilitySystemComponent::ClientEffectApplied);

	const FSCR_GameplayTags& GameplayTags = FSCR_GameplayTags::Get();
}

void USCR_AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const USCR_GameplayAbility* SCR_Ability = Cast<USCR_GameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(SCR_Ability->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void USCR_AbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.IsActive())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
		}
		// Custom toggleable ability handling

		// Bug Trigger all abilites at once
		
		/*if (InputTag.MatchesTag(SCR_GameplayTags::InputTag_Toggleable))
		{
			if (AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
			}
			else
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}*/
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
			if (InputTag.MatchesTag(SCR_GameplayTags::InputTag_MustBeHeld))
			{
				CancelAbilityHandle(AbilitySpec.Handle);
			}
			AbilitySpecInputReleased(AbilitySpec);
		}
	}

}

void USCR_AbilitySystemComponent::GrantPlayerWeaponAbilities(
	const TArray<FSCR_PlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	
 
	for (const FSCR_PlayerAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if(!AbilitySet.IsValid()) continue;
 
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
 
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void USCR_AbilitySystemComponent::RemovedGrantedPlayerWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}
 
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}
 
	InSpecHandlesToRemove.Empty();
}

void USCR_AbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                     const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

}
