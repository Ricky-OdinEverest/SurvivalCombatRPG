// Copyright Ricky Everest


#include "AnimInstances/Player/SCR_PlayerCharacterAnimInstance.h"

#include "AnimInstances/SCR_CharacterAnimInstance.h"

#include "Characters/Player/SCR_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void USCR_PlayerCharacterAnimInstance::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();
	ASCR_PlayerCharacter* PlayerCharacter = GetPlayerCharacter();
}

ASCR_PlayerCharacter* USCR_PlayerCharacterAnimInstance::GetPlayerCharacter() const
{
	return Cast<ASCR_PlayerCharacter>(OwningCharacter);
}


