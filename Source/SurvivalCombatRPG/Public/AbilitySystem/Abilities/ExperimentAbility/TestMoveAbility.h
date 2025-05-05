// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Characters/Player/SCR_PlayerCharacter.h"
#include "TestMoveAbility.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UTestMoveAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToRemoveOnEnd;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToJustApplyOnStart;
	
	TArray<FActiveGameplayEffectHandle> RemoveOnEndEffectHandles;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ASCR_PlayerCharacter* GetPlayerCharacterFromActorInfo() const;

};
