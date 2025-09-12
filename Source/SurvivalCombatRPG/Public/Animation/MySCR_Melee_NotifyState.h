// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/SCR_AnimNotifyState.h"
#include "MySCR_Melee_NotifyState.generated.h"

/**
 * Sends Gameplay Events to start and stop melee scans.
 */
UCLASS(meta = (DisplayName = "Melee Scan"))
class SURVIVALCOMBATRPG_API UMySCR_Melee_NotifyState : public USCR_AnimNotifyState
{
	GENERATED_BODY()
public:

	/**
	 * Determines if this scan uses the owner mesh that hosts this notify or a mesh from
	 * a weapon that must be obtained from the owner's Combat Manager, by a Weapon Query.
	 */
	/*UPROPERTY(EditAnywhere, Category = "Melee Scan")
	ECombatAbilitySource Source;*/

	/** Query used to retrieve the backing weapon. */
	/*UPROPERTY(EditAnywhere, Category = "Melee Scan", meta = (EditCondition = "Source == ECombatAbilitySource::Weapon", EditConditionHides))
	FGameplayTagQuery WeaponQuery;*/

	/** Enables the option to select a melee scan mesh by tag. */
	UPROPERTY(EditAnywhere, Category = "Melee Scan", meta = (InlineEditConditionToggle))
	bool bUsesComponentTag;

	/**
	 * Indicates the specific Component Tag used to find the Melee Mesh Component.
	 * Useful if the source is composed by many meshes that can participate in scans.
	 */	
	UPROPERTY(EditAnywhere, Category = "Melee Scan", meta = (EditCondition = "bUsesComponentTag"))
	FGameplayTag MeleeMeshTag;

	/** Prefix for all sockets used in this melee scan. */
	UPROPERTY(EditAnywhere, Category = "Melee Scan")
	FName ScanSocketPrefix;
	
	/*/** Class used to represent the Melee Scan. #1#
	UPROPERTY(EditAnywhere, Category = "Melee Scan", NoClear)
	TSubclassOf<USCR_MeleeScan> MeleeScanClass;*/

	/** Additional tags that can be used to define the melee scan. */
	UPROPERTY(EditAnywhere, Category = "Melee Scan")
	FGameplayTagContainer MeleeScanTags;
	
	
	UMySCR_Melee_NotifyState();
	
	// -- Begin Anim Notify State implementation
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void HandleTimeExpired(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	virtual FString GetNotifyName_Implementation() const override;
	// -- End Anim Notify State implementation

protected:

	/** Source mesh obtained used by the scan. */
	UPROPERTY()
	TObjectPtr<UMeshComponent> ScanMeshComponent;

	/**
	 * Internal helper method that allows subclasses to fully cancel the scan.
	 * At this stage, all required variables should be set.
	 */
	virtual bool CanExecuteScan();
	
	/**
	 * Attempts to retrieve the Scan Mesh from the Weapon represented by the Query.
	 */
	UFUNCTION(BlueprintCallable, Category = "SCR|Melee Scan Anim Notify State")
	void TryInitializeObjectsForWeapon(const AActor* Owner);

	/**
	 * Attempts to retrieve the Scan Mesh from the owner.
	 */
	UFUNCTION(BlueprintCallable, Category = "SCR|Melee Scan Anim Notify State")
	void InitializeObjects(const AActor* AssetSource);

	/**
	 * Ends the melee scan.
	 */
	UFUNCTION(BlueprintCallable, Category = "SCR|Melee Scan Anim Notify State")
	virtual void EndMeleeScan(USkeletalMeshComponent* MeshComp);

	/**
	 * Creates the Scan Instance from the parameters in this class.
	 */
	/*UFUNCTION(BlueprintNativeEvent, Category = "Melee Scan")
	USCR_MeleeScan* CreateMeleeScanInstance(AActor* Owner, AActor* Causer, UMeshComponent* SourceMesh, float Duration) const;*/
	
private:

	/** Tracks if this scan has started. */
	bool bHasStarted;
	
	/** Tracks if this scan has already ended. */
	bool bHasEnded;
	
	/** Identifier for the melee scan request. */
	int32 RequestId;

	/** Sockets used in the scan. */
	TArray<FName> ScanSocketNames;
};
