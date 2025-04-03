// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SCR_GameplayAbility.h"
#include "Components/Combat/SCR_EnemyCombatComponent.h"
#include "SCR_EnemyGameplayAbility.generated.h"
class ASCR_Enemy;
class ASCR_EnemyCombatComponent;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_EnemyGameplayAbility : public USCR_GameplayAbility
{

	GENERATED_BODY()
 	
public:
	UFUNCTION(BlueprintPure, Category = "SCR_Player|Ability")
	ASCR_Enemy* GetEnemyCharacterFromActorInfo();
 
	UFUNCTION(BlueprintPure, Category = "SCR_Player|Ability")
	USCR_EnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();
 
private:
	TWeakObjectPtr<ASCR_Enemy> CachedSCREnemyCharacter;
	
};
