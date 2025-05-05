// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PlayerAbilities/SCR_BaseMovement_Ability.h"
#include "SCR_Sprint_Ability.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_Sprint_Ability : public USCR_BaseMovement_Ability
{
	GENERATED_BODY()

	USCR_Sprint_Ability();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer SprintTags;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> SprintStateEffect;
	
};
