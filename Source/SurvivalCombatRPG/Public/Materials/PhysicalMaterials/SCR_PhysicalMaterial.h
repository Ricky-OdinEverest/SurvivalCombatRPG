// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "SCR_PhysicalMaterial.generated.h"

class USoundBase;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_PhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalMaterial)
	USoundBase* FootstepSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalMaterial)
	USoundBase* PointImpactSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalMaterial)
	UNiagaraSystem* PointImpactVFX = nullptr;
};
