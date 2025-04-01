// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "PlayerTypes/PlayerStructTypes.h"
#include "DataAsset_PlayerStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UDataAsset_PlayerStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(USCR_AbilitySystemComponent* InASCToGive,int32 ApplyLevel = 1) override;
 
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FSCR_PlayerAbilitySet> PlayerStartUpAbilitySets;
};
