// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "meleeExecCalc.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UmeleeExecCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UmeleeExecCalc();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
