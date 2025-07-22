// Copyright Ricky Everest


#include "AI/SCR_AIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASCR_AIController::ASCR_AIController(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) // <-- Add this line
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
}
