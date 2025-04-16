// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "SCR_AbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_AbilitySystemGlobals : public UAbilitySystemGlobals
{

	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
