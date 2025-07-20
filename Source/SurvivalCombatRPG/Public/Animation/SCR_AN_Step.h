// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "SCR_ParkourEnumTypes.h"
#include "Animation/SCR_AnimNotify.h"
#include "SCR_AN_Step.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_AN_Step : public USCR_AnimNotify
{
	GENERATED_BODY()
	
public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere)
	EFoot Foot;
	
};
