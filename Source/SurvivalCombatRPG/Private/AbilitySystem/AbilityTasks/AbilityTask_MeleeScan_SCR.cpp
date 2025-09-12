// Copyright Ricky Everest


#include "AbilitySystem/AbilityTasks/AbilityTask_MeleeScan_SCR.h"

#include "Interaction/SCR_MeleeScan.h"

DEFINE_LOG_CATEGORY(LogMeleeScanTaskSCR);

UAbilityTask_MeleeScan_SCR::UAbilityTask_MeleeScan_SCR()
{
	bTickingTask = true;
	bEnableDebug = false;
}

UAbilityTask_MeleeScan_SCR* UAbilityTask_MeleeScan_SCR::CreateTask(UGameplayAbility* OwningAbility, const bool bEnableDebug)
{
	UAbilityTask_MeleeScan_SCR* NewTask = NewAbilityTask<UAbilityTask_MeleeScan_SCR>(OwningAbility);

	NewTask->bEnableDebug = bEnableDebug;
	NewTask->StartLocation.SourceAbility = OwningAbility;
	NewTask->StartLocation.LocationType = EGameplayAbilityTargetingLocationType::ActorTransform;
	NewTask->StartLocation.SourceActor = OwningAbility->GetAvatarActorFromActorInfo();

	return NewTask;
}

void UAbilityTask_MeleeScan_SCR::Join(const USCR_MeleeScan* MeleeScan)
{
	if (!MeleeScans.Contains(MeleeScan))
	{
		USCR_MeleeScan* NonConstScan = const_cast<USCR_MeleeScan*>(MeleeScan);
		NonConstScan->bEnableDebug = bEnableDebug;
		MeleeScans.Add(NonConstScan);
	}
}

void UAbilityTask_MeleeScan_SCR::TickTask(const float DeltaTime)
{
	Super::TickTask(DeltaTime);

	for (auto It = MeleeScans.CreateIterator(); It; ++It)
	{
		USCR_MeleeScan* MeleeScan = *It;
		if (IsValid(MeleeScan) && MeleeScan->IsValidLowLevelFast())
		{
			TArray<FHitResult> Hits;
			MeleeScan->ScanForTargets(Hits);

			if (ShouldBroadcastAbilityTaskDelegates())
			{
				const FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromHitResults(Ability, Hits);
				OnMeleeTargetsFound.Broadcast(MeleeScan, TargetData);
			}
		}
		else
		{
			It.RemoveCurrent();
		}
	}
}
