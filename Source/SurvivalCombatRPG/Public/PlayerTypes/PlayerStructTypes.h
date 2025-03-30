// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"

#include "PlayerStructTypes.generated.h"

class USCR_PlayerLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FSCR_PlayerWeaponData
{
	GENERATED_BODY()
 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<USCR_PlayerLinkedAnimLayer> WeaponAnimLayerToLink;
};
