// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
//#include "Items/Weapons/SCR_PlayerWeaponBase.h"
#include "PlayerCombatComponent.generated.h"

class ASCR_PlayerWeaponBase;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	ASCR_PlayerWeaponBase* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
	
};
