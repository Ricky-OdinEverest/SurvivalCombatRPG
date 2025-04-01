// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PlayerStructTypes.generated.h"

class USCR_PlayerLinkedAnimLayer;
class UInputMappingContext;
class USCR_GameplayAbility;

USTRUCT(BlueprintType)
struct FSCR_PlayerAbilitySet
{
	GENERATED_BODY()
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USCR_GameplayAbility> AbilityToGrant;
 
	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FSCR_PlayerWeaponData
{
	GENERATED_BODY()
 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<USCR_PlayerLinkedAnimLayer> WeaponAnimLayerToLink;
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FSCR_PlayerAbilitySet> DefaultWeaponAbilities;
};
