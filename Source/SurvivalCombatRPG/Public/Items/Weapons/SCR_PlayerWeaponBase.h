// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/SCR_WeaponBase.h"
#include "PlayerTypes/PlayerStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "SCR_PlayerWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_PlayerWeaponBase : public ASCR_WeaponBase
{
	GENERATED_BODY()
	
public:

	ASCR_PlayerWeaponBase();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData", Replicated)
	FSCR_PlayerWeaponData PlayerWeaponData;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
 
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
 
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
