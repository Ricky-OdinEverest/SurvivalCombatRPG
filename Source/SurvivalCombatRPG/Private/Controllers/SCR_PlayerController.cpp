// Copyright Ricky Everest


#include "Controllers/SCR_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/SCR_EnhancedInputComponent.h"
#include "SCR_GameplayTags.h"

#include "SCR_DebugHelper.h"
#include "GameFramework/Character.h"

ASCR_PlayerController::ASCR_PlayerController()
{
	bReplicates = true;
}

void ASCR_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	Debug::Print(TEXT("Working"));

	checkf(InputConfigDataAsset,TEXT("Forgot to assign a valid data asset as input config"));
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext,0);

	}
}
void ASCR_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	
	USCR_EnhancedInputComponent* SCR_EnhancedInputComponent = CastChecked<USCR_EnhancedInputComponent>(InputComponent);

	SCR_EnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset,SCR_GameplayTags::InputTag_Move,ETriggerEvent::Triggered,this,&ThisClass::Input_Move);
	SCR_EnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset,SCR_GameplayTags::InputTag_Look,ETriggerEvent::Triggered,this,&ThisClass::Input_Look);
	SCR_EnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset,SCR_GameplayTags::InputTag_Jump,ETriggerEvent::Triggered,this,&ThisClass::Input_Jump);

}


void ASCR_PlayerController::Input_Move(const FInputActionValue& InputActionValue)
{	
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f,GetControlRotation().Yaw,0.f);
	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (MovementVector.Y != 0.f) ControlledPawn->AddMovementInput(ForwardDirection,MovementVector.Y);
		if (MovementVector.X != 0.f) ControlledPawn->AddMovementInput(RightDirection,MovementVector.X);
	}
	
}

void ASCR_PlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (LookAxisVector.X != 0.f) ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		if (LookAxisVector.Y != 0.f) ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
	

}

void ASCR_PlayerController::Input_Jump(const FInputActionValue& InputActionValue)
{
	if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn())) ControlledCharacter->Jump();
}
