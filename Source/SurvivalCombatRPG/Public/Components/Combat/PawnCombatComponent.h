// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class ASCR_WeaponBase;


UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

USTRUCT(BlueprintType)
struct FWeaponEntry
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag WeaponTag;

	UPROPERTY()
	ASCR_WeaponBase* Weapon = nullptr;
};

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	// Registers a spawned weapon. Only the server should register.
	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ASCR_WeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	ASCR_WeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	ASCR_WeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	void ToggleWeaponCollision(bool bShouldEnable,EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void PrintWeaponMap() const;

	void DropWeapon() const;

	//Update 8/29
	virtual void OnHitTargetActor(const FHitResult& HitResult);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	TArray<AActor*> OverlappedActors;
	
	// Transient TMap built locally for quick lookup.
	TMap<FGameplayTag, ASCR_WeaponBase*> CharacterCarriedWeaponMap;

	

	// Replicated array of weapon entries.
	UPROPERTY(ReplicatedUsing = OnRep_WeaponEntries)
	TArray<FWeaponEntry> ReplicatedWeaponEntries;

	// Replicated tag for currently equipped weapon.
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_WeaponEntries,  Category = "Player|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION()
	void OnRep_WeaponEntries();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;




};
