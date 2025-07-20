// Copyright Ricky Everest


#include "AbilitySystem/Abilities/SCR_MeleeAttack.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

FVector USCR_MeleeAttack::GetMeleeRotationWarpTarget()
{
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!Character)
	{
		return FVector::ZeroVector;
	}
	
	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	if (!MovementComponent)
	{
		return FVector::ZeroVector;
	}

	FVector Acceleration = MovementComponent->GetCurrentAcceleration();
	
	if (Acceleration.IsNearlyZero())
	{
		return Character->GetActorForwardVector();
	}
	
	FVector Direction = Acceleration.GetSafeNormal();

	return Direction;
}
