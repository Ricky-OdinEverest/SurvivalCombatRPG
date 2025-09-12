// Copyright Ricky Everest


#include "Interaction/SCR_MeleeScan.h"


USCR_MeleeScan::USCR_MeleeScan()
{
	bEnableDebug = false;
	bAllowMultipleHitsOnSameTarget = false;
	Duration = 1.5f;
	MeleeScanTags = FGameplayTagContainer::EmptyContainer;
}

void USCR_MeleeScan::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = MeleeScanTags;
}

USCR_MeleeScan* USCR_MeleeScan::NewInstance(TSubclassOf<USCR_MeleeScan> MeleeScanClass, AActor* Owner,
                                            AActor* Instigator, AActor* Causer, UMeshComponent* ScanMesh, const TArray<FName>& SocketNames,
                                            FVector ShapeDimensions, float Duration)
{
	const UClass* SafeMeleeScanClass = IsValid(MeleeScanClass) ? MeleeScanClass.Get() : StaticClass(); 
	USCR_MeleeScan* MeleeScan = NewObject<USCR_MeleeScan>(Owner, SafeMeleeScanClass);
	
	MeleeScan->ScanOwner = Owner;
	MeleeScan->Instigator = Cast<APawn>(Instigator);
	MeleeScan->Causer = Causer;
	MeleeScan->ScanMesh = ScanMesh;
	MeleeScan->SocketNames = SocketNames;
	MeleeScan->Duration = Duration;
	
	MeleeScan->SnapshotSocketPositions();
	return MeleeScan;
}

bool USCR_MeleeScan::HasValidScanData() const
{
	if (ScanOwner == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Melee Scan requires a a valid Scan Owner."));
		return false;
	}

	if (ScanMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning,  TEXT("Melee Scan requires a valid Mesh Component."));
		return false;
	}
	
	if (SocketNames.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Melee Scan requires at least one Socket name."));
		return false;
	}	
	
	for (const FName& SocketName : SocketNames)
	{
		if (!ScanMesh->DoesSocketExist(SocketName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Mesh %s does not have socket %s."), *GetNameSafe(ScanMesh), *SocketName.ToString());
			return false;
		}
	}

	return true;
}

/*TSubclassOf<UGameplayEffect> USCR_MeleeScan::GetMeleeHitOverride() const
{
	return MeleeHitOverride;
}*/

void USCR_MeleeScan::AppendGameplayTags(FGameplayTagContainer TagsToAdd)
{
	MeleeScanTags.AppendTags(TagsToAdd);
}

/*void USCR_MeleeScan::SetMeleeHitOverride(const TSubclassOf<UGameplayEffect>& NewMeleeHitOverride)
{
}*/

/*void USCR_MeleeScan::SetTrailGameplayCue(FGameplayTag NewTrailGameplayCueTag)
{
}*/

void USCR_MeleeScan::SnapshotSocketPositions()
{
	for (const FName& SocketName : SocketNames)
	{
		if (ScanMesh->DoesSocketExist(SocketName))
		{
			const FVector Location = ScanMesh->GetSocketLocation(SocketName);
			LastSocketPositions.Add(SocketName, Location);
		}
	}
}

void USCR_MeleeScan::ScanForTargets_Implementation(TArray<FHitResult>& OutHits)
{
	    if (!IsValid(ScanOwner)) return;

    const UWorld* World = ScanOwner->GetWorld();
    if (!IsValid(World)) return;

	const FCollisionObjectQueryParams  ObjectParams = CreateObjectParams();
    const FCollisionQueryParams TraceParams = CreateTraceParams();

    for (int32 SocketIdx = 0; SocketIdx < SocketNames.Num(); ++SocketIdx)
    {
        const FName SocketName = SocketNames[SocketIdx];

        const FVector LastSocketPosition = *LastSocketPositions.Find(SocketName);
        const FVector SocketPosition = ScanMesh->GetSocketLocation(SocketName);
        const FQuat SocketRotation = ScanMesh->GetSocketQuaternion(SocketName);
        LastSocketPositions[SocketName] = SocketPosition;

        TArray<FHitResult> HitResults;
    	
            const auto PerformLineTrace = [&](const int32 OtherIdx)
            {
                const FVector OtherSocketPosition = ScanMesh->GetSocketLocation(SocketNames[OtherIdx]);
                World->LineTraceMultiByObjectType(HitResults, SocketPosition, OtherSocketPosition, ObjectParams, TraceParams);
                DrawScanLine(LastSocketPosition, OtherSocketPosition);
            };

            const int32 LastIdx = SocketIdx - 1;
            const int32 NextIdx = SocketIdx + 1;

            if (SocketNames.IsValidIndex(LastIdx))
            {
                PerformLineTrace(LastIdx);
            }
            else if (SocketNames.IsValidIndex(NextIdx))
            {
                PerformLineTrace(NextIdx);
            }

            World->LineTraceMultiByObjectType(HitResults, LastSocketPosition, SocketPosition, ObjectParams, TraceParams);
            DrawScanLine(LastSocketPosition, SocketPosition);
        


        for (const FHitResult& NewHit : HitResults)
        {
        	bool bShouldAddHit = true;

        	if (!bAllowMultipleHitsOnSameTarget)
        	{
        		// Was the target ever found in this scan before?
        		bShouldAddHit = !OutHits.ContainsByPredicate([&](const FHitResult& Hit)
					{ return NewHit.GetActor() == Hit.GetActor(); });
        		
        		if (bShouldAddHit)
        		{
        			// Was the target already found in this current scan frame?
        			bShouldAddHit = !ConsolidatedHits.ContainsByPredicate([&](const FHitResult& Hit)
						{ return NewHit.GetActor() == Hit.GetActor(); });
        		}
        	}
        	
            if (bShouldAddHit)
            {
                OutHits.Add(NewHit);
                ConsolidatedHits.Add(NewHit);
                //DrawNewTarget(NewHit);
            }
        }
    }
}

TArray<AActor*> USCR_MeleeScan::GetIgnoredActors_Implementation() const
{
	TArray<AActor*> IgnoredActors;

	if (IsValid(ScanOwner))
	{
		ScanOwner->GetAttachedActors(IgnoredActors);
		IgnoredActors.Add(ScanOwner);	
	}
	
	return IgnoredActors;
}

FCollisionObjectQueryParams USCR_MeleeScan::CreateObjectParams() const
{
	FCollisionObjectQueryParams QueryParams;

		if (QueryParams.IsValidObjectQuery(ECollisionChannel::ECC_Pawn))
		{
			QueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);	
		}
	

	return QueryParams;
}

FCollisionQueryParams USCR_MeleeScan::CreateTraceParams() const
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(GetCombatTargets));
	TraceParams.TraceTag = TEXT("MeleeScanTrace");
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.bTraceComplex = true;

	TArray<AActor*> IgnoredActors = GetIgnoredActors();
	for (const AActor* AttachedActor : IgnoredActors)
	{
		TraceParams.AddIgnoredActor(AttachedActor);
	}
	
	return TraceParams;
}

void USCR_MeleeScan::DrawScanLine(const FVector& StartPosition, const FVector& EndPosition) const
{
#if WITH_EDITOR
	if (bEnableDebug)
	{
		const UWorld* World = ScanOwner->GetWorld();
		const float LifeTime = 1.5f;
		::DrawDebugLine(World, StartPosition, EndPosition, FColor::Red, false, LifeTime);
	}
#endif
}

/*
void USCR_MeleeScan::DrawScanSweep(const FVector& StartPosition, const FQuat& Rotation) const
{
}

void USCR_MeleeScan::DrawNewTarget(const FHitResult& NewHit) const
{
}
*/
