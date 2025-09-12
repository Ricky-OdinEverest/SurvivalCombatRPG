// Copyright Ricky Everest


#include "Components/Combat/SCR_EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "SCR_DebugHelper.h"
#include "SCR_GameplayTags.h"
#include "SCR_MeleeBPFunctionLibrary.h"

void USCR_EnemyCombatComponent::OnHitTargetActor(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if (OverlappedActors.Contains(HitActor))
	{

		return;
	}
	//Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" is hitting ") + HitActor->GetActorNameOrLabel());

	OverlappedActors.AddUnique(HitActor);

	//TODO:: Implement block check
	bool bIsValidBlock = false;
	//Is player Currently Blocking
	const bool bIsPlayerBlocking = USCR_MeleeBPFunctionLibrary::NativeDoesActorHaveTag(HitActor,SCR_GameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		//Is the the block valid
		bIsValidBlock = USCR_MeleeBPFunctionLibrary::IsValidBlock(GetOwningPawn(),HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
//8//22
	EventData.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromHitResult(HitResult);


	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		HitActor,
		SCR_GameplayTags::Player_Event_SuccessfulBlock,
		EventData
);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			SCR_GameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}
