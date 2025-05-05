// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PlayerAbilities/SCR_BaseMovement_Ability.h"
#include "SCR_Jump_GameplayAbility.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_Jump_GameplayAbility : public USCR_BaseMovement_Ability
{
	GENERATED_BODY()
	
	USCR_Jump_GameplayAbility();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnLanded(EMovementMode NewMovementMode);

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer InAirTags;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag WallRunStateTag;

	UPROPERTY(EditDefaultsOnly)
	float OffWallJumpStrength = 100.f;
};
