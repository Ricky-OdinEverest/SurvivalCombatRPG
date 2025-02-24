// Copyright Ricky Everest


#include "Characters/Player/SCR_PlayerState.h"

#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "AbilitySystem/SCR_AttributeSet.h"

ASCR_PlayerState::ASCR_PlayerState()
{
	
	AbilitySystemComponent = CreateDefaultSubobject<USCR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<USCR_AttributeSet>("AttributeSet");
	// How often Server is Updated for clients
	// 100.f 
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ASCR_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
