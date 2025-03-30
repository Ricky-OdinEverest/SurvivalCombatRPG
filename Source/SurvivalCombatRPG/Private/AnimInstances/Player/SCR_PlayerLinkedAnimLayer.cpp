// Copyright Ricky Everest


#include "AnimInstances/Player/SCR_PlayerLinkedAnimLayer.h"

#include "AnimInstances/Player/SCR_PlayerCharacterAnimInstance.h"


USCR_PlayerCharacterAnimInstance* USCR_PlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<USCR_PlayerCharacterAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

