// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCR_WeaponBase.generated.h"

class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate,AActor*)

UCLASS()
class SURVIVALCOMBATRPG_API ASCR_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASCR_WeaponBase();

	UFUNCTION(NetMulticast, Reliable)
	void HandleDrop();

	FOnTargetInteractedDelegate OnWeaponHitTarget;
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
 
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox;}
};
