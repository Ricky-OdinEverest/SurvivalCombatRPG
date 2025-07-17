// Copyright Ricky Everest


#include "AbilitySystem/Abilities/SCR_TestComboAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "GameplayTagsManager.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"


USCR_TestComboAbility::USCR_TestComboAbility()
{
	//AbilityTags.AddTag(UCAbilitySystemStatics::GetBasicAttackAbilityTag());
	//BlockAbilitiesWithTag.AddTag(UCAbilitySystemStatics::GetBasicAttackAbilityTag());
	
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

FGameplayTag USCR_TestComboAbility::GetComboChangedEventTag()
{
	return FGameplayTag::RequestGameplayTag("Player.Ability.Attack.TestCombo.Change");
}

FGameplayTag USCR_TestComboAbility::GetComboChangedEventEndTag()
{
	return FGameplayTag::RequestGameplayTag("Player.Ability.Attack.TestCombo.Change.end");
}

void USCR_TestComboAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &USCR_TestComboAbility::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &USCR_TestComboAbility::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &USCR_TestComboAbility::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &USCR_TestComboAbility::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();

		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GetComboChangedEventTag(), nullptr, false, false);
		WaitComboChangeEventTask->EventReceived.AddDynamic(this, &USCR_TestComboAbility::ComboChangedEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();
	}
	NextComboName = NAME_None;
	SetupWaitComboInputPress();

	UE_LOG(LogTemp, Display, TEXT("Combo Active"));
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USCR_TestComboAbility::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPress->OnPress.AddDynamic(this, &USCR_TestComboAbility::HandleInputPress);
	WaitInputPress->ReadyForActivation();
}

void USCR_TestComboAbility::HandleInputPress(float TimeWaited)
{
	//SetupWaitComboInputPress();
	TryCommitCombo();
}

void USCR_TestComboAbility::TryCommitCombo()
{
	if (NextComboName == NAME_None)
	{
		return;
	}

	UAnimInstance* OwnerAnimInst = GetOwnerAnimInstance();
	if (!OwnerAnimInst)
	{
		return;
	}

	//OwnerAnimInst->Montage_SetNextSection(OwnerAnimInst->Montage_GetCurrentSection(ComboMontage), NextComboName, ComboMontage);
	OwnerAnimInst->Montage_JumpToSection( NextComboName, ComboMontage);

	
}

class UAnimInstance* USCR_TestComboAbility::GetOwnerAnimInstance() const
{
	USkeletalMeshComponent* OwnerSkeletalMeshComp = GetOwningComponentFromActorInfo();
	if (OwnerSkeletalMeshComp)
	{
		return OwnerSkeletalMeshComp->GetAnimInstance();
	}
	return nullptr;
}

void USCR_TestComboAbility::ComboChangedEventReceived(FGameplayEventData Data)
{


	FGameplayTag EventTag = Data.EventTag;

	if (EventTag == GetComboChangedEventEndTag())
	{
		NextComboName = NAME_None;
		UE_LOG(LogTemp, Display, TEXT("next combo cleared"));
		return;
	}
	
	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);

	NextComboName = TagNames.Last();

	UE_LOG(LogTemp, Display, TEXT("next Combo is now: %s"), *NextComboName.ToString());
}

/*
void USCR_TestComboAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
*/
