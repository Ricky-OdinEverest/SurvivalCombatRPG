// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "SCR_ComboManagerInterface.h"
#include "Components/StateTreeComponent.h"
#include "SCR_ComboManagerComponent.generated.h"

class UStateTreeSchema;
/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class SURVIVALCOMBATRPG_API USCR_ComboManagerComponent : public UStateTreeComponent, public ISCR_ComboManagerInterface
{
	GENERATED_BODY()
	
};
