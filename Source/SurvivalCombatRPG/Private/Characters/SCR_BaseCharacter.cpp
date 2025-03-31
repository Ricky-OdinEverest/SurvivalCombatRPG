// Copyright Ricky Everest


#include "Characters/SCR_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "SurvivalCombatRPG/SurvivalCombatRPG.h"

// Sets default values
ASCR_BaseCharacter::ASCR_BaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	GetMesh()->bReceivesDecals = false;

}

UAbilitySystemComponent* ASCR_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector ASCR_BaseCharacter::GetCombatSocketLocation()
{
	return GetMesh()->GetSocketLocation(SpellSocketName);
}

FVector ASCR_BaseCharacter::GetRightHandSwordSocketLocation()
{
	return GetMesh()->GetSocketLocation("Weapon_R");
	
}

void ASCR_BaseCharacter::InitAbilityActorInfo()
{
}

void ASCR_BaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ASCR_BaseCharacter::InitializeDefaultAttributes() const
{


	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ASCR_BaseCharacter::AddCharacterAbilities()
{
	USCR_AbilitySystemComponent* SCR_ASC = CastChecked<USCR_AbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	SCR_ASC->AddCharacterAbilities(StartupAbilities);
}

