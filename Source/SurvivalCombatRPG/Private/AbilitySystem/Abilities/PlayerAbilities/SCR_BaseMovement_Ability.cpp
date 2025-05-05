// Copyright Ricky Everest


#include "AbilitySystem/Abilities/PlayerAbilities/SCR_BaseMovement_Ability.h"
#include "AbilitySystemLog.h"

void USCR_BaseMovement_Ability::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                const FGameplayAbilityActorInfo* ActorInfo, 
                                                const FGameplayAbilityActivationInfo ActivationInfo,
                                                const FGameplayEventData* TriggerEventData)
{
   // Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent->MakeEffectContext();

    for (auto GameplayEffect : OngoingEffectsToJustApplyOnStart)
    {
        if (!GameplayEffect.Get()) continue;

        if (UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get())
        {
            FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
            if (SpecHandle.IsValid())
            {
                FActiveGameplayEffectHandle ActiveGEHandle = AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
                if (!ActiveGEHandle.WasSuccessfullyApplied())
                {
                    ABILITY_LOG(Log, TEXT("Ability %s failed to apply startup effect %s"), *GetName(), *GetNameSafe(GameplayEffect));
                }
            }
        }
    }
} 

void USCR_BaseMovement_Ability::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, 
                                           const FGameplayAbilityActivationInfo ActivationInfo, 
                                           bool bReplicateEndAbility, 
                                           bool bWasCancelled)
{
    if (IsInstantiated())
    {
        for (FActiveGameplayEffectHandle ActiveEffectHandle : RemoveOnEndEffectHandles)
        {
            if (ActiveEffectHandle.IsValid())
            {
                ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle);
            }
        }

        RemoveOnEndEffectHandles.Empty();
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
