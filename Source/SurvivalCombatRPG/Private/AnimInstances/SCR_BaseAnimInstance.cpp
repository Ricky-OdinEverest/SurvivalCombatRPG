// Copyright Ricky Everest


#include "AnimInstances/SCR_BaseAnimInstance.h"
#include "SCR_MeleeBPFunctionLibrary.h"

bool USCR_BaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return USCR_MeleeBPFunctionLibrary::NativeDoesActorHaveTag(OwningPawn,TagToCheck);
	}

	return false;
}
