// Copyright Ricky Everest


#include "AbilitySystem/Abilities/PlayerAbilities/SCR_Sprint_Ability.h"

#include "AbilitySystemLog.h"
#include "Characters/Player/SCR_PlayerCharacter.h"
#include "Components/Movement/SCR_MovementComponent.h"

USCR_Sprint_Ability::USCR_Sprint_Ability()
{
}

void USCR_Sprint_Ability::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	//if (!SprintStateEffect.Get()) return;

	/*if (UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
	{
		//FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(SprintStateEffect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			if (!ActiveGEHandle.WasSuccessfullyApplied())
			{
				ABILITY_LOG(Log, TEXT("Ability %s failed to apply crouch effect %s"), *GetName(), *GetNameSafe(SprintStateEffect));
			}
		}
	}*/

	MovementComponent = Cast<USCR_MovementComponent>(GetPlayerCharacterFromActorInfo()->GetCharacterMovement());
	if (MovementComponent)
	{
		float SprintSpeed = MovementComponent->GetMaxSpeed() * 2;
	}
}

void USCR_Sprint_Ability::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ABILITY_LOG(Log, TEXT("Ended"), *GetName(), *GetNameSafe(SprintStateEffect));
}
