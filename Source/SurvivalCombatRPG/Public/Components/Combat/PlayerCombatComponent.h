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
	// For now give Player Character class access to everything on this combat component
	friend class ASCR_PlayerCharacter;
	
	
	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	ASCR_PlayerWeaponBase* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	ASCR_PlayerWeaponBase* GetPlayerCurrentEquippedWeapon() const;
 
	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	float GetPlayerCurrentEquippWeaponDamageAtLevel(float InLevel) const;

//Update 8/29
	virtual void OnHitTargetActor(const FHitResult& HitResult) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
	
private:
	class ASCR_PlayerCharacter* PlayerCharacter;
	
};


