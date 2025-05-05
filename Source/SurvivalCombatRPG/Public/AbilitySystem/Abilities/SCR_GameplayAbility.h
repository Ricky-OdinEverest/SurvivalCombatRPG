// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PlayerTypes/PlayerStructTypes.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "SCR_GameplayAbility.generated.h"

class UPawnCombatComponent;
class USCR_PlayerGameplayAbility;

UENUM(BlueprintType)
enum class ESCR_AbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
	
	

	
protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "Player_Ability")
	ESCR_AbilityActivationPolicy AbilityActivationPolicy = ESCR_AbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Player_Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Player_Ability")
	USCR_AbilitySystemComponent* GetPlayerAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,const FGameplayEffectSpecHandle& InSpecHandle);
 
	UFUNCTION(BlueprintCallable, Category = "Player_Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,const FGameplayEffectSpecHandle& InSpecHandle,EPlayerSuccessType& OutSuccessType);

//Effects

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToRemoveOnEnd;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToJustApplyOnStart;
	
	TArray<FActiveGameplayEffectHandle> RemoveOnEndEffectHandles;
};