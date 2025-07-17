// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SCR_GameplayAbility.h"
#include "SCR_TestHeavyComboAbility.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_TestHeavyComboAbility : public USCR_GameplayAbility
{
	GENERATED_BODY()
	
	/*USCR_TestHeavyComboAbility();
	//~ Begin UGameplayAbility Interface.

public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	FGameplayTag GetComboChangedEventTag();
	static FGameplayTag GetComboChangedEventEndTag();
	//static FGameplayTag GetComboTargetEventTag();

protected:
	class UAnimInstance* GetOwnerAnimInstance() const;

private:
	void SetupWaitComboInputPress();

	UFUNCTION()
	void HandleInputPress(float TimeWaited);

	void TryCommitCombo();

	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ComboMontage;

	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Data);
	
	FName NextComboName;*/
};
