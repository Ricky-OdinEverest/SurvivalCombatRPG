// Copyright Ricky Everest


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/SCR_WeaponBase.h"
#include "SCR_DebugHelper.h"
#include "Net/UnrealNetwork.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                 ASCR_WeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{

	// Ensure we only register on the server.
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	// Check for duplicate registration in our local map.
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister))
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon with tag %s already registered; skipping duplicate registration."), *InWeaponTagToRegister.ToString());
		return;
	}
	
	//checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister),TEXT("A  named %s has already been added as carried weapon"),*InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);
	
	check(InWeaponToRegister);

	// Set ownership on the spawned weapon
	AActor* OwnerActor = GetOwner();
	InWeaponToRegister->SetOwner(OwnerActor);
	if (APawn* PawnOwner = Cast<APawn>(OwnerActor))
	{
		InWeaponToRegister->SetInstigator(PawnOwner);
	}
 
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister,InWeaponToRegister);

	// Also update the replicated array.
	FWeaponEntry NewEntry;
	NewEntry.WeaponTag = InWeaponTagToRegister;
	NewEntry.Weapon = InWeaponToRegister;
	ReplicatedWeaponEntries.Add(NewEntry);
 
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
 
	//const FString WeaponString = FString::Printf(TEXT("Weapon %s registered with tag %s"),
	//	*InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	//Debug::Print(WeaponString);
}

ASCR_WeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (ASCR_WeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}
 
	return nullptr;
}

ASCR_WeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
 
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::PrintWeaponMap() const
{
	for (const auto& Elem : CharacterCarriedWeaponMap)
	{
		FString WeaponName = Elem.Value ? Elem.Value->GetName() : TEXT("None");
		FString DebugString = FString::Printf(TEXT("Weapon Tag: %s, Weapon Name: %s"), *Elem.Key.ToString(), *WeaponName);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DebugString);
		UE_LOG(LogTemp, Log, TEXT("%s"), *DebugString);
	}
}

void UPawnCombatComponent::DropWeapon() const
{
	if (ASCR_WeaponBase* Weapon = GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag))
	{
		Weapon->HandleDrop();
	}
}



void UPawnCombatComponent::OnRep_WeaponEntries()
{
	// Rebuild the local TMap from the replicated array.
	CharacterCarriedWeaponMap.Empty();
	for (const FWeaponEntry& Entry : ReplicatedWeaponEntries)
	{
		CharacterCarriedWeaponMap.Add(Entry.WeaponTag, Entry.Weapon);
	}
}

void UPawnCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate array of weapon entries.
	DOREPLIFETIME(UPawnCombatComponent, ReplicatedWeaponEntries);
	DOREPLIFETIME(UPawnCombatComponent, CurrentEquippedWeaponTag);
}
