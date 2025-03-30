#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SCR_EquipAbilityTask.generated.h"

class ASCR_PlayerWeaponBase;
class UPlayerCombatComponent;
class USCR_PlayerGameplayAbility;

USTRUCT()
struct FGameplayAbilityTargetData_Weapon : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

public:
	// Pointer to your weapon actor
	UPROPERTY()
	TWeakObjectPtr<ASCR_PlayerWeaponBase> Weapon;

	// Pointer to your player combat component
	UPROPERTY()
	TWeakObjectPtr<UPlayerCombatComponent> PCC;

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_Weapon::StaticStruct();
	}

	virtual FString ToString() const override
	{
		return TEXT("FGameplayAbilityTargetData_Weapon");
	}
};

/** Delegate to broadcast the DataHandle that contains the weapon info */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponDataSignature,
											const FGameplayAbilityTargetDataHandle&, DataHandle);



UCLASS()
class SURVIVALCOMBATRPG_API USCR_EquipAbilityTask : public UAbilityTask
{
	GENERATED_BODY()
    
public:
	/** Creates an instance of this ability task */
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta=(DisplayName="SCR_EquipAbilityTask", 
			  HidePin="OwningAbility", 
			  DefaultToSelf="OwningAbility", 
			  BlueprintInternalUseOnly="true"))
	static USCR_EquipAbilityTask* Create_EquippedWeaponData(UGameplayAbility* OwningAbility);

	/** Called when the weapon data is successfully found & replicated (to both server/clients) */
	UPROPERTY(BlueprintAssignable)
	FWeaponDataSignature OnWeaponData;

private:
	// Core AbilityTask interface
	virtual void Activate() override;

	/**
	 * Example function that:
	 * 1) Builds a FGameplayAbilityTargetData_Weapon with the found weapon
	 * 2) Calls ServerSetReplicatedTargetData to replicate it
	 * 3) Broadcasts OnWeaponData locally
	 */
	void SendWeaponData(ASCR_PlayerWeaponBase* InWeapon, UPlayerCombatComponent* InPCC);

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag) const;
};


