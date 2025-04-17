// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SCR_AIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ASCR_AIController();
protected:
 
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};

