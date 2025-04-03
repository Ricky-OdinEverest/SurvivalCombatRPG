// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class USCR_EnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

	
public:
	virtual void GiveToAbilitySystemComponent(USCR_AbilitySystemComponent* InASCToGive,int32 ApplyLevel = 1) override;
 
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < USCR_EnemyGameplayAbility > > EnemyCombatAbilities;
	
};
