// Copyright Ricky Everest


#include "Characters/Enemy/SCR_EnemyBase.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "AbilitySystem/SCR_AttributeSet.h"

ASCR_EnemyBase::ASCR_EnemyBase()
{

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<USCR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<USCR_AttributeSet>("AttributeSet");
	
}

void ASCR_EnemyBase::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();

}

void ASCR_EnemyBase::InitAbilityActorInfo()
{

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<USCR_AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
