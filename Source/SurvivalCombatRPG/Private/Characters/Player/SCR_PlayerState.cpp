// Copyright Ricky Everest


#include "Characters/Player/SCR_PlayerState.h"

#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "AbilitySystem/SCR_AttributeSet.h"
#include "Net/UnrealNetwork.h"

ASCR_PlayerState::ASCR_PlayerState()
{
	
	AbilitySystemComponent = CreateDefaultSubobject<USCR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USCR_AttributeSet>("AttributeSet");
	
	// How often Server is Updated for clients
	// 100.f 
	NetUpdateFrequency = 100.f;
}

void ASCR_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ASCR_PlayerState, Level);
}

void ASCR_PlayerState::OnRep_Level(int32 OldLevel)
{
}

UAbilitySystemComponent* ASCR_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
