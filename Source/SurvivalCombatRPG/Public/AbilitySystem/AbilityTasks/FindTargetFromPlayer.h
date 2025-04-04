// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "FindTargetFromPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UFindTargetFromPlayer : public UAbilityTask
{
	GENERATED_BODY()

public:
 
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName = "TargetFromPlayer", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UFindTargetFromPlayer* CreateTargetFromPlayer(UGameplayAbility* OwningAbility);
 
	UPROPERTY(BlueprintAssignable)
	FPlayerTargetDataSignature ValidData;
 
private:
 
	virtual void Activate() override;
	void SendAimData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
 
};
