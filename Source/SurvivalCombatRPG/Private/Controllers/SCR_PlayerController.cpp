// Copyright Ricky Everest


#include "Controllers/SCR_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/SCR_InputConfig.h"
#include "Components/Input/SCR_EInputComponent.h"
#include "SCR_GameplayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "SCR_DebugHelper.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/EnemyInterface.h"

ASCR_PlayerController::ASCR_PlayerController()
{
	bReplicates = true;
}

void ASCR_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	Debug::Print(TEXT("Working"));

	checkf(InputConfig,TEXT("Forgot to assign a valid data asset as input config"));
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputConfig->DefaultMappingContext,0);

	}
}
void ASCR_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	
	USCR_EInputComponent* SCR_EnhancedInputComponent = CastChecked<USCR_EInputComponent>(InputComponent);

	SCR_EnhancedInputComponent->BindNativeInputAction(InputConfig,SCR_GameplayTags::InputTag_Move,ETriggerEvent::Triggered,this,&ThisClass::Input_Move);
	SCR_EnhancedInputComponent->BindNativeInputAction(InputConfig,SCR_GameplayTags::InputTag_Look,ETriggerEvent::Triggered,this,&ThisClass::Input_Look);
	SCR_EnhancedInputComponent->BindNativeInputAction(InputConfig,SCR_GameplayTags::InputTag_Jump,ETriggerEvent::Triggered,this,&ThisClass::Input_Jump);

	
	//SCR_EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASCR_PlayerController::Input_Move);
	SCR_EnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

}


USCR_AbilitySystemComponent* ASCR_PlayerController::GetASC()
{
	if(SCR_AbilitySystemComponent == nullptr)
	{
		SCR_AbilitySystemComponent = Cast<USCR_AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
		
	}
	return SCR_AbilitySystemComponent;
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

void ASCR_PlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	/**
	 * Line trace from cursor. There are several scenarios:
	 *  A. LastActor is null && ThisActor is null
	 *		- Do nothing
	 *	B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null
	 *		- UnHighlight LastActor
	 *	D. Both actors are valid, but LastActor != ThisActor
	 *		- UnHighlight LastActor, and Highlight ThisActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing
	 */
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A - both are null, do nothing
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E - do nothing
			}
		}
	}
}

void ASCR_PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FSCR_GameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void ASCR_PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FSCR_GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
 
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
				}
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void ASCR_PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FSCR_GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
 
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
 
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}
 
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}
