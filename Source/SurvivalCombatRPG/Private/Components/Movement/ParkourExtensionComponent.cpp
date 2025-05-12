// Copyright Ricky Everest


#include "Components/Movement/ParkourExtensionComponent.h"
#include "UI/Widgets/SCR_UserWidget.h"
#include "Characters/Player/SCR_PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "SCR_DebugHelper.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


UParkourExtensionComponent::UParkourExtensionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	minVaultingHeight = 50.0f;
	minVaultingHeight = 170.0f;
}

void UParkourExtensionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<ASCR_PlayerCharacter>(GetOwningPawn());
	if (VaultWidgetClass)
	{
		// Create the widget
		 VaultWidget = CreateWidget<UUserWidget>(GetWorld(), VaultWidgetClass);
	}
	
	CanPlayerVault();
}

void UParkourExtensionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CanPlayerVault();

	
}

bool UParkourExtensionComponent::CanPlayerVault()
{
	if (UCapsuleComponent* Caspule = PlayerCharacter->GetCapsuleComponent())
	{
		FHitResult HitResult;

		float PlayerHalfHeight = Caspule->GetScaledCapsuleHalfHeight();
		const FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		const FVector Start  = (PlayerLocation + (PlayerCharacter->GetActorForwardVector() * 70.0f)) + FVector(0.f, 0.f, PlayerHalfHeight) ;
		const FVector End = (PlayerLocation + (PlayerCharacter->GetActorForwardVector() * 70.0f)) - FVector(0.f, 0.f, PlayerHalfHeight) ;
		
		// Draw debug line (green if no hit, red if hit)
		FColor LineColor = FColor::Red;
		
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(PlayerCharacter);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldStatic, QueryParams))
		{
			if (HitResult.bBlockingHit)
			{
				LineColor = FColor::Green;
				IsValidLedgeHeight(HitResult);
				HandleShowVaultWidget();
				DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);
				return true;
			}
			if (!HitResult.bBlockingHit)
			{
				EndingLocation = FVector::ZeroVector;
				DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);
				HandleHideVaultWidget();
				return false;
				
			}
		}
		
	}
	HandleHideVaultWidget();
	return false;
}

bool UParkourExtensionComponent::CanPlayerVaultToHitLocation(UCapsuleComponent* const& Capsule,
	FHitResult& OutHitResult)
{
	FVector EndingLocationLocal = FVector::ZeroVector;
	return false;
	
}

bool UParkourExtensionComponent::IsValidLedgeHeight(FHitResult& OutHitResult)
{
	
	float height = OutHitResult.Location.Z  + OutHitResult.TraceEnd.Z;
	const FString DebugHeight = FString::Printf(TEXT("%f H"), height);
	
	if (!(height >= minVaultingHeight && height <= maxVaultingHeight))
	{
		Debug::Print(DebugHeight, height);
		return false;
	}
	Debug::Print(DebugHeight, height);
	return true;
}

bool UParkourExtensionComponent::IsLedgeWalkableSurface(FHitResult& OutHitResult)
{
	float QueryLedgeSurface = OutHitResult.Normal.Z;
	float AcceptableLedgeSurface =  PlayerCharacter->GetCharacterMovement()->GetWalkableFloorZ();

	return QueryLedgeSurface < AcceptableLedgeSurface;
}

/*bool UParkourExtensionComponent::IsValidSpaceOnLedge(FHitResult& OutHitResult, UCapsuleComponent* const& Capsule)
{
	float PlayerHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
	FVector LocalEndingLocation = OutHitResult.Location + FVector(0.0f,0.0f , PlayerHalfHeight);
	FVector LocalEndingPlayerHeight = LocalEndingLocation + FVector(0.0f,0.0f ,Capsule->GetScaledCapsuleRadius());

	if (PlayerCharacter)
	{
		// Get the capsule component of the player
		
		if (Capsule)
		{
			TArray<AActor*> OverlappingActors;
            
			// Get overlapping actors (this automatically uses the capsule's radius and half-height)
			Capsule->GetOverlappingActors(OverlappingActors);

			// Iterate over overlapping actors and do something with them
			for (AActor* Actor : OverlappingActors)
			{
				if (Actor)
				{
					// Process each actor that is overlapping with the capsule
					UE_LOG(LogTemp, Log, TEXT("Overlapping Actor: %s"), *Actor->GetName());
				}
			}
		}
	}

}*/


void UParkourExtensionComponent::HandleShowVaultWidget()
{
			if (VaultWidget && !VaultWidget->IsInViewport())
			{
				VaultWidget->AddToViewport();
			}
}


void UParkourExtensionComponent::HandleHideVaultWidget()
{
	if (VaultWidget && VaultWidget->IsInViewport())
	{
		VaultWidget->RemoveFromParent();
	}
}

