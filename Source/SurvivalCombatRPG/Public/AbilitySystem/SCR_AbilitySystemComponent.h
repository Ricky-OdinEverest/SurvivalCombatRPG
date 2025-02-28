// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SCR_AbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();
	
protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};
