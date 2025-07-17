// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/SCR_AnimNotify.h"
#include "SCR_SendGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_SendGameplayEvent : public USCR_AnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
private:
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FGameplayTag EventTag;
	virtual FString GetNotifyName_Implementation() const; 
};
