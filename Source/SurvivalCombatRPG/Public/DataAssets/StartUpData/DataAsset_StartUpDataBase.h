// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class USRC_GameplayAbility;
class USCR_AbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(USCR_AbilitySystemComponent* InASCToGive,int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < USRC_GameplayAbility > > ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < USRC_GameplayAbility > > ReactiveAbilities;

	void GrantAbilities(const TArray< TSubclassOf < USRC_GameplayAbility > >& InAbilitiesToGive,USCR_AbilitySystemComponent* InASCToGive,int32 ApplyLevel = 1);
};