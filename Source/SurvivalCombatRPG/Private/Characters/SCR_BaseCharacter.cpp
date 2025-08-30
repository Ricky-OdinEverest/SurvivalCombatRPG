// Copyright Ricky Everest


#include "Characters/SCR_BaseCharacter.h"
#include "Components/Movement/Effects/SCR_FootStepComponent.h"
#include "AbilitySystemComponent.h"
#include "MotionWarpingComponent.h"
#include "SCR_GameplayTags.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/SCR_WeaponBase.h"
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

	OptionalWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("OptionalWeapon");
	
	OptionalWeapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	OptionalWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FootstepsComponent = CreateDefaultSubobject<USCR_FootStepComponent>(TEXT("FootstepsComponent"));
	
	Nat_MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("Nat_MotionWarpingComponent"));

}
// This is identical aside from the object initializer parameter that allows for an alternate movement component class
ASCR_BaseCharacter::ASCR_BaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->bReceivesDecals = false;

	OptionalWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("OptionalWeapon");
	OptionalWeapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	OptionalWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FootstepsComponent = CreateDefaultSubobject<USCR_FootStepComponent>(TEXT("FootstepsComponent"));

	Nat_MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("Nat_MotionWarpingComponent"));
}

UAbilitySystemComponent* ASCR_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ASCR_BaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ASCR_BaseCharacter::Die()
{
	OptionalWeapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	
	MulticastHandleDeath();
}

void ASCR_BaseCharacter::MulticastHandleDeath_Implementation()
{
	OptionalWeapon->SetSimulatePhysics(true);
	OptionalWeapon->SetEnableGravity(true);
	OptionalWeapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
 	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();
	bDead = true;
}

FVector ASCR_BaseCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	/*if (OptionalWeapon->GetSkeletalMeshAsset() != nullptr)
	{
		return OptionalWeapon->GetSocketLocation(SpellSocketName);
	}
	return GetMesh()->GetSocketLocation(SpellSocketName);*/

	const FSCR_GameplayTags& GameplayTags = FSCR_GameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Weapon) && IsValid(OptionalWeapon))
	{
		return OptionalWeapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_LeftHand_Spell))
	{
		return GetMesh()->GetSocketLocation(SpellSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Grunt_Mace))
	{
		return GetPawnCombatComponent()->GetCharacterCarriedWeaponByTag(SCR_GameplayTags::Enemy_Weapon)->WeaponMesh->
		                                 GetSocketLocation("MaceSocket");
	}
	

	
	return FVector();
}

bool ASCR_BaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

AActor* ASCR_BaseCharacter::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> ASCR_BaseCharacter::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* ASCR_BaseCharacter::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

UPawnCombatComponent* ASCR_BaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

USCR_FootStepComponent* ASCR_BaseCharacter::GetFootstepsComponent() const
{
	return FootstepsComponent;
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

// In Aura Character Startup abilities live in an Array on the Player Character.
// It seems that if I want to expand the functionility to allow weapons to grant abilities I have to use the data asset setup from warrior gas

void ASCR_BaseCharacter::AddCharacterAbilities()
{
	USCR_AbilitySystemComponent* SCR_ASC = CastChecked<USCR_AbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	SCR_ASC->AddCharacterAbilities(StartupAbilities);
}

void ASCR_BaseCharacter::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		OptionalWeapon->SetMaterial(0, DynamicMatInst);
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}

