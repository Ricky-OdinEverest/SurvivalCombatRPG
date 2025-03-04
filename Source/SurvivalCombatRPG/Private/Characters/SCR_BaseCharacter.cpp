// Copyright Ricky Everest


#include "Characters/SCR_BaseCharacter.h"
#include "AbilitySystemComponent.h"

// Sets default values
ASCR_BaseCharacter::ASCR_BaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

}

UAbilitySystemComponent* ASCR_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASCR_BaseCharacter::InitAbilityActorInfo()
{
}

void ASCR_BaseCharacter::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}
