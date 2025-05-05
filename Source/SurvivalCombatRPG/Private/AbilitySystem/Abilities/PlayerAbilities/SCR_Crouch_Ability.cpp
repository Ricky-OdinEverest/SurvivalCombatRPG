// Copyright Ricky Everest


#include "AbilitySystem/Abilities/PlayerAbilities/SCR_Crouch_Ability.h"

#include "AbilitySystemLog.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework/Character.h"

USCR_Crouch_Ability::USCR_Crouch_Ability()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool USCR_Crouch_Ability::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                             const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character) return false;

	// Allow activation regardless of crouch state
	// Maybe use in fututure to Block Crouch
	return true;

	
}

void USCR_Crouch_Ability::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());

	if (Character->bIsCrouched)
	{
		Character->UnCrouch();
		FGameplayTag EndCrouchTag = FGameplayTag::RequestGameplayTag(FName("Event.Movement.OnEndCrouch"));
	
		UAbilityTask_WaitGameplayEvent* WaitForEndCrouch = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EndCrouchTag, nullptr, false, true);
	
		if (WaitForEndCrouch)
		{
			WaitForEndCrouch->EventReceived.AddDynamic(this, &USCR_Crouch_Ability::OnEndCrouchReceived);
			WaitForEndCrouch->Activate();
		}
		
		
	}
	else
	{
		Character->Crouch();
		FGameplayTag StartCrouchTag = FGameplayTag::RequestGameplayTag(FName("Event.Movement.OnStartCrouch"));
	
		UAbilityTask_WaitGameplayEvent* WaitForEndCrouch = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, StartCrouchTag, nullptr, false, true);
	
		if (WaitForEndCrouch)
		{
			WaitForEndCrouch->EventReceived.AddDynamic(this, &USCR_Crouch_Ability::OnStartCrouchReceived);
			WaitForEndCrouch->Activate();
		}

		if (!CrouchStateEffect.Get()) return;

		if (UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CrouchStateEffect, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				if (!ActiveGEHandle.WasSuccessfullyApplied())
				{
					ABILITY_LOG(Log, TEXT("Ability %s failed to apply crouch effect %s"), *GetName(), *GetNameSafe(CrouchStateEffect));
				}
			}
		}
		
		//EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
	
}

void USCR_Crouch_Ability::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	if (Character->bIsCrouched)
	{
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
	else
	{
		UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		if (AbilitySystemComponent && CrouchStateEffect.Get())
		{
			AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(CrouchStateEffect, AbilitySystemComponent);
		}
	
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
	
}

void USCR_Crouch_Ability::OnEndCrouchReceived(FGameplayEventData Payload)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void USCR_Crouch_Ability::OnStartCrouchReceived(FGameplayEventData Payload)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}


/*void AActionGameCharacter::OnCrouchActionStarted(const FInputActionValue& Value)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(CrouchTags, true);
	}
}*/

/*void AActionGameCharacter::OnCrouchActionEnded(const FInputActionValue& Value)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAbilities(&CrouchTags);
	}
}*/