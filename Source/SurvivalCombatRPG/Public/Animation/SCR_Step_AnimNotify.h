// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Animation/SCR_AnimNotify.h"
#include "SCR_MeleeEnumTypes.h"  
#include "SCR_Step_AnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_Step_AnimNotify : public USCR_AnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;  
  
	UPROPERTY(EditAnywhere)  
	EFoot Foot;  
	
};
