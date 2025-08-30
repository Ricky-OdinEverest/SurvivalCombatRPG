// Copyright Ricky Everest


#include "Components/Combat/SCR_EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "SCR_DebugHelper.h"
#include "SCR_GameplayTags.h"

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

	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		//TODO::check if the block is valid
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
//8//22
	EventData.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromHitResult(HitResult);


	if (bIsValidBlock)
	{
		//TODO::Handle successful block
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
