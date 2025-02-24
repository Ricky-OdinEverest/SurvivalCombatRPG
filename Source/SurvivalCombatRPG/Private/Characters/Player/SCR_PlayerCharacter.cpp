// Copyright Ricky Everest
#include "Characters/Player/SCR_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "SCR_DebugHelper.h"
#include "Characters/Player/SCR_PlayerState.h"

ASCR_PlayerCharacter::ASCR_PlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f,96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = CameraBoomLength;
	CameraBoom->SocketOffset = FVector(0.f,55.f,65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName(TEXT("katana_Targer01")));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Scabbard = CreateDefaultSubobject<UStaticMeshComponent>("Scabbard");
	Scabbard->SetupAttachment(GetMesh(), FName(TEXT("Scabbard_Target01")));
	Scabbard->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ASCR_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Debug::Print(TEXT("Working"));
}

void ASCR_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
	if (AbilitySystemComponent && AttributeSet)
	{
		const FString ASCText = FString::Printf(TEXT("Owner Actor: %s, AvatarActor: %s"),*AbilitySystemComponent->GetOwnerActor()->GetActorLabel(),*AbilitySystemComponent->GetAvatarActor()->GetActorLabel());
		
		Debug::Print(TEXT("Ability system component valid. ") + ASCText,FColor::Green);
		Debug::Print(TEXT("AttributeSet valid. ") + ASCText,FColor::Green);
	}
	
}

void ASCR_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void ASCR_PlayerCharacter::InitAbilityActorInfo()
{
	

	ASCR_PlayerState* SCR_PlayerState = GetPlayerState<ASCR_PlayerState>();
	check(SCR_PlayerState);
	SCR_PlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SCR_PlayerState, this);
	AbilitySystemComponent = SCR_PlayerState->GetAbilitySystemComponent();
	AttributeSet = SCR_PlayerState->GetAttributeSet();
}
