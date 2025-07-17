// Copyright Ricky Everest


#include "AbilitySystem/Abilities/SCR_TestHeavyComboAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

/*
USCR_TestHeavyComboAbility::USCR_TestHeavyComboAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void USCR_TestHeavyComboAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}

	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);

		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &USCR_TestHeavyComboAbility::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &USCR_TestHeavyComboAbility::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &USCR_TestHeavyComboAbility::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &USCR_TestHeavyComboAbility::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();

		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GetComboChangedEventTag(), nullptr, false, false);
		WaitComboChangeEventTask->EventReceived.AddDynamic(this, &USCR_TestHeavyComboAbility::ComboChangedEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();
	}
	SetupWaitComboInputPress();

	UE_LOG(LogTemp, Display, TEXT("Combo Active"));
}
*/
