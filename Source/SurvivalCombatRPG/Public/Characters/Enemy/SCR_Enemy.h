// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemy/SCR_EnemyBase.h"
#include "SCR_Enemy.generated.h"

class USCR_EnemyCombatComponent;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_Enemy : public ASCR_EnemyBase
{
	GENERATED_BODY()
public:
	ASCR_Enemy();


protected:

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	USCR_EnemyCombatComponent* EnemyCombatComponent;

	virtual void Die() override;

private:
	void InitEnemyStartUpData() const;
 
public:
	FORCEINLINE USCR_EnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent;}
};