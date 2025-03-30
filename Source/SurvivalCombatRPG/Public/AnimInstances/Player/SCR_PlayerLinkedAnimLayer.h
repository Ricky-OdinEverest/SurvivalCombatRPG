// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/SCR_BaseAnimInstance.h"
#include "SCR_PlayerLinkedAnimLayer.generated.h"

class USCR_PlayerCharacterAnimInstance;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_PlayerLinkedAnimLayer : public USCR_BaseAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	USCR_PlayerCharacterAnimInstance* GetPlayerAnimInstance() const;
};
