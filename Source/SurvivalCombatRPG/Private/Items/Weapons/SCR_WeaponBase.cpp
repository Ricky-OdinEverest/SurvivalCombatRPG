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
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionBoxEndOverlap);
	
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
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
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


