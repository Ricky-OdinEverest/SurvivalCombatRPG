// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SCR_DamageGameplayAbility.h"
#include "SCR_ProjectileSpell.generated.h"

class ASCR_Projectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_ProjectileSpell : public USCR_DamageGameplayAbility
{
	GENERATED_BODY()
	
protected:
 
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASCR_Projectile> ProjectileClass;
	

 	
};
