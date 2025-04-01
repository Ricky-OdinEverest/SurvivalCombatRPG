// Copyright Ricky Everest


#include "PlayerTypes/PlayerStructTypes.h"
#include "AbilitySystem/Abilities/PlayerAbilities/SCR_PlayerGameplayAbility.h"

bool FSCR_PlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
