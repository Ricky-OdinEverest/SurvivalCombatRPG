// Copyright Ricky Everest


#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "SCR_GameplayTags.h"
void USCR_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USCR_AbilitySystemComponent::EffectApplied);

	const FSCR_GameplayTags& GameplayTags = FSCR_GameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Orange,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
		);
}

void USCR_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

}
