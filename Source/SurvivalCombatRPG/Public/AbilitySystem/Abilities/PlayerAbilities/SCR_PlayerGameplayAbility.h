// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SCR_GameplayAbility.h"
#include "SCR_PlayerGameplayAbility.generated.h"

class ASCR_PlayerCharacter;
class ASCR_PlayerController;

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_PlayerGameplayAbility : public USCR_GameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "SCR_Player|Ability")
	ASCR_PlayerCharacter* GetPlayerCharacterFromActorInfo();
 
	UFUNCTION(BlueprintPure, Category = "SCR_Player|Ability")
	ASCR_PlayerController* GetPlayerControllerFromActorInfo();
 
	UFUNCTION(BlueprintPure, Category = "SCR_Player|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "SCR_Player|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,float InWeaponBaseDamage,FGameplayTag InCurrentAttackTypeTag,int32 InUsedComboCount);
private:
	TWeakObjectPtr<ASCR_PlayerCharacter> CachedSCRPlayerCharacter;
	TWeakObjectPtr<ASCR_PlayerController> CachedSCRPlayerController;
};
