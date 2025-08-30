// Copyright Ricky Everest


#include "Components/Combat/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"

#include "Items/Weapons/SCR_PlayerWeaponBase.h"
#include "Net/UnrealNetwork.h"
#include "SCR_DebugHelper.h"
#include "SCR_GameplayTags.h"


ASCR_PlayerWeaponBase* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ASCR_PlayerWeaponBase>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

ASCR_PlayerWeaponBase* UPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
	return Cast<ASCR_PlayerWeaponBase>(GetCharacterCurrentEquippedWeapon());
}

float UPlayerCombatComponent::GetPlayerCurrentEquippWeaponDamageAtLevel(float InLevel) const
{
	return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}
//Update 8/29
void UPlayerCombatComponent::OnHitTargetActor(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();

	if (!HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("No HitActor in FHitResult"));
		return;
	}
	
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
 
	OverlappedActors.AddUnique(HitActor);


 
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	//8/22
	Data.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromHitResult(HitResult);

	
 
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		SCR_GameplayTags::Shared_Event_MeleeHit,
		Data
	);
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		SCR_GameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}

void UPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		 GetOwningPawn(),
		 SCR_GameplayTags::Player_Event_HitPause,
		 FGameplayEventData()
	 );
}

