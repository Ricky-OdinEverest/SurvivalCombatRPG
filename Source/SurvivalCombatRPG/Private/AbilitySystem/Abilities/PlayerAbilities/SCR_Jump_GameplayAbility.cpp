// Copyright Ricky Everest


#include "AbilitySystem/Abilities/PlayerAbilities/SCR_Jump_GameplayAbility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SCR_DebugHelper.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitMovementModeChange.h"

USCR_Jump_GameplayAbility::USCR_Jump_GameplayAbility()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool USCR_Jump_GameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                                   const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);

	// Bind to landed delegate
	
 	return Character->CanJump();
}

void USCR_Jump_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			return;
		}
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		
		ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
		if (Character->IsLocallyControlled())
		{
			Character->UnCrouch();
			Character->Jump();
		}
		
		UAbilityTask_WaitMovementModeChange* WaitForLanding = UAbilityTask_WaitMovementModeChange::CreateWaitMovementModeChange(this, EMovementMode::MOVE_Walking);
		WaitForLanding->OnChange.AddDynamic(this, &USCR_Jump_GameplayAbility::OnLanded);
		WaitForLanding->ReadyForActivation();

		/*if (UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext();

			FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(JumpEffect, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

				if (!ActiveGEHandle.WasSuccessfullyApplied())
				{
					Debug::Print(TEXT("Failed to apply jump effect"));
				}
			}
		}*/
		
	}

}

void USCR_Jump_GameplayAbility::OnLanded(EMovementMode NewMovementMode)
{

	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		ASC->RemoveActiveEffectsWithTags(InAirTags);
	}
	if (NewMovementMode == MOVE_Walking && IsActive())
	{

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}


}






