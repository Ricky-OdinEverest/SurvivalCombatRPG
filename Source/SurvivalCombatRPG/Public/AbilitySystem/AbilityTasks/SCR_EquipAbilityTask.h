
#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/Abilities/SCR_AbilityTypes.h" // Include the new header
#include "SCR_EquipAbilityTask.generated.h"

class ASCR_PlayerWeaponBase;
class UPlayerCombatComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponDataSignature,
	const FGameplayAbilityTargetDataHandle&, DataHandle);

UCLASS()
class SURVIVALCOMBATRPG_API USCR_EquipAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Ability Task|Output")
	TObjectPtr<ASCR_PlayerWeaponBase> EquippedWeapon = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Ability Task|Output")
	TObjectPtr<UPlayerCombatComponent> OwningPCC = nullptr;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta=(DisplayName="SCR_EquipAbilityTask",
		HidePin="OwningAbility",
		DefaultToSelf="OwningAbility",
		BlueprintInternalUseOnly="true"))
	static USCR_EquipAbilityTask* Create_EquippedWeaponData(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FWeaponDataSignature OnWeaponData;

protected:
	virtual void Activate() override;
	void SendWeaponData(ASCR_PlayerWeaponBase* InWeapon, UPlayerCombatComponent* InPCC);
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
	virtual void OnDestroy(bool AbilityIsEnding) override;
};


