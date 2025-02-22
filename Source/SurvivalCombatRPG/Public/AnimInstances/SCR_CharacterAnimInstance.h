// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/SCR_BaseAnimInstance.h"
#include "SCR_CharacterAnimInstance.generated.h"


class ASCR_BaseCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_CharacterAnimInstance : public USCR_BaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	ASCR_BaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FVector Velocity;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bIsFalling;
	
};
