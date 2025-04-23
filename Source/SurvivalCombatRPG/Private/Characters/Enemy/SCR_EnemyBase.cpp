// Copyright Ricky Everest


#include "Characters/Enemy/SCR_EnemyBase.h"

#include "SCR_GameplayTags.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "AbilitySystem/SCR_AbilitySystemLibrary.h"
#include "AbilitySystem/SCR_AttributeSet.h"
#include "AI/SCR_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SurvivalCombatRPG/SurvivalCombatRPG.h"
#include "UI/Widgets/SCR_UserWidget.h"

ASCR_EnemyBase::ASCR_EnemyBase()
{

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<USCR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
 

	AttributeSet = CreateDefaultSubobject<USCR_AttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ASCR_EnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!HasAuthority()) return;
	SCR_AIController = Cast<ASCR_AIController>(NewController);
	SCR_AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	SCR_AIController->RunBehaviorTree(BehaviorTree);
	SCR_AIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	SCR_AIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
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

void ASCR_EnemyBase::Die()
{
	SetLifeSpan(LifeSpan);
	
	Super::Die();
}

void ASCR_EnemyBase::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ASCR_EnemyBase::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}


void ASCR_EnemyBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (!HasAuthority()) return;
	if (SCR_AIController && SCR_AIController->GetBlackboardComponent())
	{
		SCR_AIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
	
}

void ASCR_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	

	if (HasAuthority())
	{
	USCR_AbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);	}
 
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

				
		AbilitySystemComponent->RegisterGameplayTagEvent(FSCR_GameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ASCR_EnemyBase::HitReactTagChanged
		);
 
		OnBloodChanged.Broadcast(AS->GetBlood());
		OnMaxBloodhChanged.Broadcast(AS->GetMaxBlood());
	}
}

void ASCR_EnemyBase::InitAbilityActorInfo()
{

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<USCR_AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();		
	}
}

void ASCR_EnemyBase::InitializeDefaultAttributes() const
{
	USCR_AbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
