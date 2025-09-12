// Copyright Ricky Everest


#include "Animation/MySCR_Melee_NotifyState.h"

#include "SCR_MeleeBPFunctionLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Interaction/SCR_MeleeScan.h"

UMySCR_Melee_NotifyState::UMySCR_Melee_NotifyState()
{

}

void UMySCR_Melee_NotifyState::NotifyBegin(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	/*Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	AActor* Owner = MeshComp->GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}

	//UPawnCombatComponent* CombatManager = USCR_MeleeBPFunctionLibrary::NativeGetPawnCombatComponentFromActor(Owner)
	/*if (!IsValid(CombatManager))
	{
		return;
	}#1#
	
	/*if (Source == ECombatAbilitySource::Owner)
	{
		InitializeObjects(Owner);
	}
	else
	{#1#
		TryInitializeObjectsForWeapon(Owner);
//	}

	AActor* Causer = IsValid(ScanMeshComponent) ? ScanMeshComponent->GetOwner() : nullptr;
	if (IsValid(Causer) && CanExecuteScan())
	{
		//USCR_MeleeScan* MeleeScan = CreateMeleeScanInstance(Owner, Causer, ScanMeshComponent, TotalDuration);
		checkf(IsValid(MeleeScan), TEXT("Sanity Check: Unable to create a Melee Scan."));
		
		/*COMBAT_LOG_ARGS(Verbose, "Created Melee Scan '%s': owner '%s', causer '%s' and mesh ' %s'.",
			*GetNameSafe(MeleeScan), *GetNameSafe(Owner), *GetNameSafe(Causer), *GetNameSafe(ScanMeshComponent));#1#

		MeleeScan->AppendGameplayTags(MeleeScanTags);
		//RequestId = CombatManager->RegisterMeleeScanRequest(MeleeScan);
		bHasStarted = true;*/
	}


void UMySCR_Melee_NotifyState::HandleTimeExpired(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation)
{
	//Super::HandleTimeExpired(MeshComp, Animation);
	EndMeleeScan(MeshComp);
}

FString UMySCR_Melee_NotifyState::GetNotifyName_Implementation() const
{
	return "Melee Scan";
}

bool UMySCR_Melee_NotifyState::CanExecuteScan()
{
	return true;
}

void UMySCR_Melee_NotifyState::TryInitializeObjectsForWeapon(const AActor* Owner)
{
	//const TScriptInterface<ICombatWeaponInterface> WeaponScript = FNinjaCombatAnimNotifyHelpers::GetWeapon(Owner, WeaponQuery);
//	const AActor* Causer = Cast<AActor>(WeaponScript.GetObject());
		
	/*if (IsValid(Causer))
	{
		InitializeObjects(Causer);
	}
	else
	{
#if !WITH_EDITOR
		// Only log this warning in the game. No point doing it in the animation editor.
		COMBAT_LOG_ARGS(Warning, "Weapon Query %s did not return a valid weapon!", *WeaponQuery.GetDescription());
#endif
	}*/
}

void UMySCR_Melee_NotifyState::InitializeObjects(const AActor* AssetSource)
{
	if (IsValid(AssetSource))
	{
		// First use the interface as may provide fast access to the component.
		//if (AssetSource->Implements<UCombatMeleeInterface>())
		{
			if (bUsesComponentTag && MeleeMeshTag.IsValid())
			{
			//	ScanMeshComponent = ICombatMeleeInterface::Execute_GetMeleeMeshByTag(AssetSource, MeleeMeshTag);
			}
			else
			{
			//	ScanMeshComponent = ICombatMeleeInterface::Execute_GetMeleeMesh(AssetSource);
			}
		}

		// As a fallback, try to find the component tagged with the melee scan source tag.
		if (ScanMeshComponent == nullptr)
		{
			//const FName Tag = Tag_Combat_Component_MeleeScanSource.GetTag().GetTagName();
			//ScanMeshComponent = AssetSource->FindComponentByTag<UMeshComponent>(Tag);	
		}

		// Retrieve the sockets from the mesh.
		if (IsValid(ScanMeshComponent))
		{
			const FString SocketPrefixString = ScanSocketPrefix.ToString();
			const TArray<FName>& AllSockets = ScanMeshComponent->GetAllSocketNames();

			ScanSocketNames = AllSockets.FilterByPredicate([SocketPrefixString](const FName& SocketName)
			{
				const FString SocketString = SocketName.ToString();
				return SocketString.StartsWith(SocketPrefixString);
			});
		}
	}
}

void UMySCR_Melee_NotifyState::EndMeleeScan(USkeletalMeshComponent* MeshComp)
{
	/*if (!bHasStarted || bHasEnded)
	{
		return;
	}
	
	const AActor* Owner = MeshComp->GetOwner();
	if (!IsValid(Owner) || RequestId == INDEX_NONE)
	{
		return;
	}

	//UNinjaCombatManagerComponent* CombatManager = UNinjaCombatFunctionLibrary::GetCombatManagerComponent(Owner);
	//if (!IsValid(CombatManager))
	{
		return;
	}
	
	//CombatManager->CancelMeleeScanRequest(RequestId);
	bHasEnded = true;*/
}

