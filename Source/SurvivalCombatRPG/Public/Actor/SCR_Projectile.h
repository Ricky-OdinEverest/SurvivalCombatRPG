// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCR_Projectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SURVIVALCOMBATRPG_API ASCR_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCR_Projectile();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
 
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
 
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;
 
	bool bHit = false;
 	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
 
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
 
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
 
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;
 
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;

};
