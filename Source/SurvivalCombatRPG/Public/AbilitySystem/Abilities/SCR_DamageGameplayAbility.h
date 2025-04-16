// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SCR_GameplayAbility.h"
#include "SCR_DamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_DamageGameplayAbility : public USCR_GameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
 
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
	
};
