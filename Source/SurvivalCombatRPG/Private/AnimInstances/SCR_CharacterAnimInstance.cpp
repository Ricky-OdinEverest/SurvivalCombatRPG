// Copyright Ricky Everest


#include "AnimInstances/SCR_CharacterAnimInstance.h"
#include "Characters/SCR_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void USCR_CharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ASCR_BaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void USCR_CharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	
	Velocity = OwningCharacter->GetVelocity();
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bIsFalling = OwningMovementComponent->IsFalling();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
}
