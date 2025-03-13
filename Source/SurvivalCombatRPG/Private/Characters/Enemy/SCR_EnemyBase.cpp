// Copyright Ricky Everest


#include "Characters/Enemy/SCR_EnemyBase.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "AbilitySystem/SCR_AttributeSet.h"
#include "SurvivalCombatRPG/SurvivalCombatRPG.h"

ASCR_EnemyBase::ASCR_EnemyBase()
{

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<USCR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<USCR_AttributeSet>("AttributeSet");
	
}

void ASCR_EnemyBase::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void ASCR_EnemyBase::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}

int32 ASCR_EnemyBase::GetPlayerLevel()
{
	return Level;
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
