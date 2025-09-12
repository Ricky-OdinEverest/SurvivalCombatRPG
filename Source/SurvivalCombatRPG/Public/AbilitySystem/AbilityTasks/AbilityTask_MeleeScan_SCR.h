// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_MeleeScan_SCR.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMeleeScanTaskSCR, Log, All);

class USCR_MeleeScan;

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UAbilityTask_MeleeScan_SCR : public UAbilityTask
{
	GENERATED_BODY()
	
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSCRMeleeScan, const USCR_MeleeScan*, MeleeScan, const FGameplayAbilityTargetDataHandle&, Data);

	/** Broadcasts targets that we hit during the scan. */
	UPROPERTY(BlueprintAssignable)
	FSCRMeleeScan OnMeleeTargetsFound;

	UAbilityTask_MeleeScan_SCR();

	// -- Begin Ability Task implementation
	virtual void TickTask(float DeltaTime) override;
	// -- End Ability Task implementation

	/**
	 * Creates the appropriate Ability Task, based on the provided data.
	 */
	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Ability|Tasks")
	static UAbilityTask_MeleeScan_SCR* CreateTask(UGameplayAbility* OwningAbility, bool bEnableDebug = false);

	/**
	 * Adds a new Melee Scan to this task.
	 */
	UFUNCTION(BlueprintCallable, Category = "SCR|Ability Tasks")
	void Join(const USCR_MeleeScan* MeleeScan);

protected:

	/** Sets this task to debug mode. */
	bool bEnableDebug;

	/** The start location used for the target broadcast. */
	FGameplayAbilityTargetingLocationInfo StartLocation;

	/** Current list of targets that were found. */
	TArray<FHitResult> HitResults;

	/** All instances participating in this scan. */
	UPROPERTY()
	TArray<TObjectPtr<USCR_MeleeScan>> MeleeScans;
};