// Copyright Ricky Everest


#include "Items/Weapons/SCR_WeaponBase.h"


#include "Components/BoxComponent.h"
#include "SCR_DebugHelper.h"
#include "SCR_MeleeBPFunctionLibrary.h"
// Sets default values
ASCR_WeaponBase::ASCR_WeaponBase()
{
	// Set replication on the weapon actor
	bReplicates = true;
	AActor::SetReplicateMovement(true);
	
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false); // Start disabled

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionBoxEndOverlap);
	
}

void ASCR_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	// Perform the sweep each tick while overlapping
	if (bIsOverlappingHostile)
	{
		PerformBoxSweep();
	}
		
	
}

void ASCR_WeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
 
	checkf(WeaponOwningPawn,TEXT("Forgot to assign an instiagtor as the owning pawn of the weapon: %s"),*GetName());
 
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (USCR_MeleeBPFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn,HitPawn))
		{
			//  Enable ticking when a hostile is overlapping
			bIsOverlappingHostile = true;
			SetActorTickEnabled(true);
			
			/*FVector BoxExtent = WeaponCollisionBox->GetScaledBoxExtent();
			FVector Start = WeaponCollisionBox->GetComponentLocation();
			FVector End = Start; // No movement; trace at current position
			FRotator BoxRotation = WeaponCollisionBox->GetComponentRotation();

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);
			QueryParams.AddIgnoredActor(WeaponOwningPawn);
			QueryParams.bTraceComplex = true;

			FHitResult TraceHit;

			bool bHit = GetWorld()->SweepSingleByChannel(
				TraceHit,
				Start,
				End,
				BoxRotation.Quaternion(),
				ECC_Pawn, 
				FCollisionShape::MakeBox(BoxExtent),
				QueryParams
			);
#if WITH_EDITOR
			// Debug draw
			DrawDebugBox(GetWorld(), Start, BoxExtent, BoxRotation.Quaternion(), bHit ? FColor::Red : FColor::Green, false, 2.0f);
#endif
			if (bHit && TraceHit.GetActor() == OtherActor)
			{
				UE_LOG(LogTemp, Log, TEXT("Valid trace confirmed: %s"), *TraceHit.GetActor()->GetName());
				OnWeaponHitTarget.ExecuteIfBound(TraceHit);
			}
			else if (bHit)
			{
				UE_LOG(LogTemp, Warning, TEXT("Trace hit %s, but it does not match overlap actor %s — ignoring."),
					*TraceHit.GetActor()->GetName(), *OtherActor->GetName());
			}*/
		}
 
		//TODO:Implement hit check for enemy characters
	}
}

void ASCR_WeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
 
	checkf(WeaponOwningPawn,TEXT("Forgot to assign an instiagtor as the owning pawn of the weapon: %s"),*GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (USCR_MeleeBPFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn,HitPawn))
		{
			if (WeaponOwningPawn != HitPawn)
			{
				OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
				bIsOverlappingHostile = false;

				// ✅ Disable ticking when hostile ends overlap
				SetActorTickEnabled(false);
			}
 
			//TODO:Implement hit check for enemy characters
		}
	}

}

void ASCR_WeaponBase::HandleDrop_Implementation()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}

void ASCR_WeaponBase::PerformBoxSweep()
{


	FVector BoxExtent = WeaponCollisionBox->GetScaledBoxExtent();
	FVector Start = WeaponCollisionBox->GetComponentLocation();
	FVector End = Start;
	FRotator BoxRotation = WeaponCollisionBox->GetComponentRotation();

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(GetInstigator());
	QueryParams.bTraceComplex = true;

	FHitResult TraceHit;

	bool bHit = GetWorld()->SweepSingleByChannel(
		TraceHit,
		Start,
		End,
		BoxRotation.Quaternion(),
		ECC_Pawn,
		FCollisionShape::MakeBox(BoxExtent),
		QueryParams
	);

#if WITH_EDITOR
	//DrawDebugBox(GetWorld(), Start, BoxExtent, BoxRotation.Quaternion(), bHit ? FColor::Red : FColor::Green, false, 0.1f);
#endif

	if (bHit && TraceHit.GetActor())
	{
		if (APawn* WeaponOwningPawn = GetInstigator<APawn>())
		{
			if (APawn* HitPawn = Cast<APawn>(TraceHit.GetActor()))
			{
				if (USCR_MeleeBPFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
				{
					
					OnWeaponHitTarget.ExecuteIfBound(TraceHit);
				//	UE_LOG(LogTemp, Log, TEXT("Tick Sweep Hit: %s"), *HitPawn->GetName());
				}
			}
		}
	}
}

