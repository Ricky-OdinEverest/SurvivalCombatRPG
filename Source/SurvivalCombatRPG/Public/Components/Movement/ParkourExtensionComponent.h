// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Characters/Player/SCR_PlayerCharacter.h"
#include "Components/PawnExtensionComponentBase.h"
#include "SCR_ParkourEnumTypes.h"
#include "ParkourExtensionComponent.generated.h"

/**
 * 
 */

#define HANDLE_VAULTING_STATE(SwitchValue) \
switch (SwitchValue) \
{ \
case ESCR_VaultingState::NotVaulting: \
UE_LOG(LogTemp, Log, TEXT("CanPlayerVault")); \
break; \
case ESCR_VaultingState::WantsToVault: \
UE_LOG(LogTemp, Log, TEXT("Wants to Vault")); \
break; \
case ESCR_VaultingState::Vaulting: \
UE_LOG(LogTemp, Log, TEXT("Vaulting")); \
break; \
default: \
UE_LOG(LogTemp, Warning, TEXT("Unknown Vaulting State")); \
break; \
}

UCLASS()
class SURVIVALCOMBATRPG_API UParkourExtensionComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	friend class ASCR_PlayerCharacter;
	UParkourExtensionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool CanPlayerVault();
	
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VaultWidget")
	TSubclassOf<class USCR_UserWidget> VaultWidgetClass;
	
	class UUserWidget* VaultWidget;
private:
	 ASCR_PlayerCharacter* PlayerCharacter;

	ESCR_VaultingState VaultingState;

	
	UPROPERTY(EditDefaultsOnly, Category = "VaultDefaults")
	float minVaultingHeight;
	UPROPERTY(EditDefaultsOnly, Category = "VaultDefaults")
	float maxVaultingHeight;
	
	bool CanPlayerVaultToHitLocation(UCapsuleComponent* const& Capsule, FHitResult& OutHitResult);

	bool IsValidLedgeHeight(FHitResult& OutHitResult);

	bool IsLedgeWalkableSurface(FHitResult& OutHitResult);

	bool IsValidSpaceOnLedge(FHitResult& OutHitResult, UCapsuleComponent* const& Capsule);

	void HandleShowVaultWidget();
	void HandleHideVaultWidget();

	FVector EndingLocation;

	/*void HandleSwitchVaultingState(ESCR_VaultingState VaultingState);*/
	
	
};

