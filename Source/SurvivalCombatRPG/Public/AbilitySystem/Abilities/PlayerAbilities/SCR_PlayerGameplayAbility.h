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
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	ASCR_PlayerCharacter* GetPlayerCharacterFromActorInfo();
 
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	ASCR_PlayerController* GetPlayerControllerFromActorInfo();
 
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();
 
private:
	TWeakObjectPtr<ASCR_PlayerCharacter> CachedSCRPlayerCharacter;
	TWeakObjectPtr<ASCR_PlayerController> CachedSCRPlayerController;
};
