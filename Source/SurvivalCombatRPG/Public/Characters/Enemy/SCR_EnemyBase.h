// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Characters/SCR_BaseCharacter.h"
#include "SCR_EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_EnemyBase : public ASCR_BaseCharacter
{
	GENERATED_BODY()

public:
	ASCR_EnemyBase();
	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
