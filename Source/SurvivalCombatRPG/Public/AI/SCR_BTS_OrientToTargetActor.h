// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SCR_BTS_OrientToTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_BTS_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()
		
	USCR_BTS_OrientToTargetActor();

	//~ Begin UBTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	//~ End UBTNode Interface

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Target")
	float RotationInterpSpeed;
};
