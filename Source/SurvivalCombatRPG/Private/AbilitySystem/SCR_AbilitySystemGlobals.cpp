// Copyright Ricky Everest


#include "AbilitySystem/SCR_AbilitySystemGlobals.h"
#include "SCR_AbilityTypes.h"

FGameplayEffectContext* USCR_AbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FSCR_GameplayEffectContext();
}