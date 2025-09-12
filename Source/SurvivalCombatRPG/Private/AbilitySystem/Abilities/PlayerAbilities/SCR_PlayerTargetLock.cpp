// Copyright Ricky Everest


#include "AbilitySystem/Abilities/PlayerAbilities/SCR_PlayerTargetLock.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Characters/Player/SCR_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/SCR_UserWidget.h"
#include "Controllers/SCR_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "SCR_DebugHelper.h"
#include "SCR_GameplayTags.h"
#include "SCR_MeleeBPFunctionLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void USCR_PlayerTargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	if (!ActorInfo || !ActorInfo->IsLocallyControlled())
	{
		return;
	}
	//replace for first pass to bias character the pawn is looking at
	TryLockOnTarget();
	InitTargetLockMovement();
	InitTargetLockMappingContext();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USCR_PlayerTargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	CleanUp();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USCR_PlayerTargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor ||
	USCR_MeleeBPFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor,SCR_GameplayTags::Shared_Status_Dead) ||
	USCR_MeleeBPFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), SCR_GameplayTags::Shared_Status_Dead)
	)
	{
		CancelTargetLockAbility();
		return;
	}

	SetTargetLockWidgetPosition();
	// while the look at rotation will always be overridden the actor rotation will only be overidden if the boolean is true
	const bool bShouldOverrideRotation =
	!USCR_MeleeBPFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(),SCR_GameplayTags::Player_Status_Rolling)
    &&
	!USCR_MeleeBPFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(),SCR_GameplayTags::Player_Status_Dodge)
	&&
	!USCR_MeleeBPFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(),SCR_GameplayTags::State_Movement_Sprint);


	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
	GetPlayerCharacterFromActorInfo()->GetActorLocation(),
	CurrentLockedActor->GetActorLocation()
	);
	const FRotator CurrentControlRot = GetPlayerControllerFromActorInfo()->GetControlRotation();
	LookAtRot -= FRotator(TargetLockCameraOffsetDistance,0.f,0.f);
	const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot,LookAtRot,DeltaTime,TargetLockRotationInterpSpeed);
	// while the look at rotation will always be overridden the actor rotation will only be overidden if the boolean is true
	if (bShouldOverrideRotation)
	{
		/*FRotator CurrentActorRotation = GetPlayerCharacterFromActorInfo()->GetActorRotation();
		FRotator NewActorRotation = FMath::RInterpTo(CurrentActorRotation, FRotator(0.f, LookAtRot.Yaw, 0.f), DeltaTime, TargetLockRotationInterpSpeed);
		GetPlayerCharacterFromActorInfo()->SetActorRotation(NewActorRotation);*/
		
		GetPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.f,TargetRot.Yaw,0.f));
	}
	
	GetPlayerControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch,TargetRot.Yaw,0.f));
}

void USCR_PlayerTargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();
	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	TArray<AActor*> ActorsAbove;
	TArray<AActor*> ActorsBelow;
	AActor* NewTargetToLock = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft,ActorsOnRight,ActorsAbove,ActorsBelow);
	
	if (InSwitchDirectionTag == SCR_GameplayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else if (InSwitchDirectionTag == SCR_GameplayTags::Player_Event_SwitchTarget_Right)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}
	else if (InSwitchDirectionTag == SCR_GameplayTags::Player_Event_SwitchTarget_Up)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsAbove);
	}
	else if (InSwitchDirectionTag == SCR_GameplayTags::Player_Event_SwitchTarget_Down)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsBelow);
	}

	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}


void USCR_PlayerTargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();
	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

//	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	CurrentLockedActor = GetBestTargetByViewCone(AvailableActorsToLock);


	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
}

void USCR_PlayerTargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();
	TArray<FHitResult> BoxTraceHits;
	
	// Angle = arccos(FOVBias), but DrawDebugCone takes half-angle in radians
	
	if (bShowPersistentDebugCone)
	{
		const FVector CamLocation = GetPlayerControllerFromActorInfo()->PlayerCameraManager->GetCameraLocation();
		const FVector CamForward = GetPlayerControllerFromActorInfo()->PlayerCameraManager->GetCameraRotation().Vector();
		const float ConeHalfAngleRadians = FMath::Acos(FOVBias);
		// Draw cone to visualize lock-on area
		DrawDebugCone(
			GetWorld(),
			CamLocation,
			CamForward,
			TraceBoxSize.X,               // Length of cone
			ConeHalfAngleRadians, // Half angle in radians
			ConeHalfAngleRadians, // Vertical and horizontal angle same
			12,                   // Num sides
			FColor::Green,
			true,
			2.0f                  // Duration
		);
	}


	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + GetPlayerCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetPlayerCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);

				//Debug::Print(HitActor->GetActorNameOrLabel());
			}
		}
	}
}

void USCR_PlayerTargetLock::DrawTargetLockWidget()
{	
	if (!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in Blueprint"));

		DrawnTargetLockWidget = CreateWidget<USCR_UserWidget>(GetPlayerControllerFromActorInfo(), TargetLockWidgetClass);

		check(DrawnTargetLockWidget);

		DrawnTargetLockWidget->AddToViewport();
	}
	else
	{
		Debug::Print("Failed to draw target lock widget !");
	}
}

AActor* USCR_PlayerTargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(),InAvailableActors,ClosestDistance);
}

void USCR_PlayerTargetLock::GetAvailableActorsAroundTarget(
	TArray<AActor*>& OutActorsOnLeft,
	TArray<AActor*>& OutActorsOnRight,
	TArray<AActor*>& OutActorsAbove,
	TArray<AActor*>& OutActorsBelow)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if(!AvailableActor || AvailableActor == CurrentLockedActor) continue;

		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
		// cross prodect apparently works on the 2d plane
		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized,PlayerToAvailableNormalized);

		if (CrossResult.Z>0.f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
	
		
		float ZDiff = AvailableActor->GetActorLocation().Z - CurrentLockedActor->GetActorLocation().Z;
		float ZThreshold = 100.f;

		if (ZDiff > ZThreshold)
		{
			OutActorsAbove.AddUnique(AvailableActor);
		}
		else if (ZDiff < -ZThreshold)
		{
			OutActorsBelow.AddUnique(AvailableActor);
		}

	}
	
}

AActor* USCR_PlayerTargetLock::GetBestTargetByViewCone(const TArray<AActor*>& InAvailableActors)
{
	AActor* BestTarget = nullptr;
	float BestScore = -1.f;

	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	//const FVector PlayerViewDir = GetPlayerControllerFromActorInfo()->PlayerCameraManager->GetCameraRotation().Vector();

	for (AActor* Target : InAvailableActors)
	{
		if (!Target) continue;

		//const FVector ToTarget = (Target->GetActorLocation() - PlayerLocation).GetSafeNormal();

		// 1 should mean I am looking right at it though it might not be exact given To target is from the player and not the camera
		const FVector CameraLocation = GetPlayerControllerFromActorInfo()->PlayerCameraManager->GetCameraLocation();
		const FVector PlayerViewDir = GetPlayerControllerFromActorInfo()->PlayerCameraManager->GetCameraRotation().Vector();
		const FVector ToTarget = (Target->GetActorLocation() - CameraLocation).GetSafeNormal();
		const float Dot = FVector::DotProduct(PlayerViewDir, ToTarget);

		if (Dot < FOVBias) continue; //  ignore targets too far outside of forward cone

		// Test bias by distance 
		const float Distance = FVector::Dist(PlayerLocation, Target->GetActorLocation());
		const float Score = Dot;

		// / (Distance + 1.f); // +1 to avoid div by zero : Bigger Distance means less likely to Target

		if (Score > BestScore)
		{
			BestScore = Score;
			BestTarget = Target;
		}
	}

	// fallback to nearest if none are in view cone
	if (!BestTarget)
	{
		return GetNearestTargetFromAvailableActors(InAvailableActors);
	}

	return BestTarget;
}




void USCR_PlayerTargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget  || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}
	
	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetPlayerControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true
	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			}
		);
	}

	ScreenPosition -= (TargetLockWidgetSize / 2.f);

	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition,false);
}

void USCR_PlayerTargetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;

	GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void USCR_PlayerTargetLock::InitTargetLockMappingContext()
{	
	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)

	Subsystem->AddMappingContext(TargetLockMappingContext,3);
}

void USCR_PlayerTargetLock::ResetTargetLockMappingContext()
{
	if (!GetPlayerControllerFromActorInfo())
	{
		return;
	}
	
	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)

	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}

void USCR_PlayerTargetLock::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed>0.f)
	{
		GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	}
}

void USCR_PlayerTargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(),GetCurrentActorInfo(),GetCurrentActivationInfo(),true);
}

void USCR_PlayerTargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();

	CurrentLockedActor = nullptr;

	if (DrawnTargetLockWidget)
	{
		DrawnTargetLockWidget->RemoveFromParent();
		
	}

	DrawnTargetLockWidget = nullptr;

	TargetLockWidgetSize = FVector2D::ZeroVector;

	CachedDefaultMaxWalkSpeed = 0.f;
}
