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

protected:
	virtual void BeginPlay() override;

	//virtual void InitAbilityActorInfo();
};
