// Copyright Ricky Everest


#include "Characters/Enemy/SCR_EnemyBase.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "AbilitySystem/SCR_AttributeSet.h"
#include "SurvivalCombatRPG/SurvivalCombatRPG.h"
#include "UI/Widgets/SCR_UserWidget.h"

ASCR_EnemyBase::ASCR_EnemyBase()
{

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<USCR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<USCR_AttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
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

 
	if (USCR_UserWidget* SCR_UserWidget = Cast<USCR_UserWidget>(HealthBar->GetUserWidgetObject()))
	{
		SCR_UserWidget->SetWidgetController(this);
	}
 	
	if (const USCR_AttributeSet* AS = Cast<USCR_AttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetBloodAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnBloodChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxBloodAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxBloodhChanged.Broadcast(Data.NewValue);
			}
		);
 
		OnBloodChanged.Broadcast(AS->GetBlood());
		OnMaxBloodhChanged.Broadcast(AS->GetMaxBlood());
	}
}

void ASCR_EnemyBase::InitAbilityActorInfo()
{

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<USCR_AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}
