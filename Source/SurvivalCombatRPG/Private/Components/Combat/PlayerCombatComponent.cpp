// Copyright Ricky Everest


#include "Components/Combat/PlayerCombatComponent.h"

#include "Items/Weapons/SCR_PlayerWeaponBase.h"
#include "Net/UnrealNetwork.h"
#include "SCR_DebugHelper.h"


ASCR_PlayerWeaponBase* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ASCR_PlayerWeaponBase>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" hit ") + HitActor->GetActorNameOrLabel(),FColor::Green);
}

void UPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("'s weapon pulled from ") + InteractedActor->GetActorNameOrLabel(),FColor::Red);
}

