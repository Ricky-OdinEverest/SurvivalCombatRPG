// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCR_WeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class SURVIVALCOMBATRPG_API ASCR_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASCR_WeaponBase();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox;}
};
