// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Characters/SCR_BaseCharacter.h"
#include "Interaction/PlayerInterface.h"
#include "SCR_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerCombatComponent;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_PlayerCharacter : public ASCR_BaseCharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ASCR_PlayerCharacter(const FObjectInitializer& ObjectInitializer);

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
	
	//~ Begin PawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface Interface
	

	virtual void PostInitializeComponents() override;

	//Reacts to calling crouch?
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UParkourExtensionComponent* ParkourExtensionComponent;

	virtual void ShowMagicCircle_Implementation(UMaterialInterface* DecalMaterial) override;
	virtual void HideMagicCircle_Implementation() override;
	
protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:

#pragma region Components

	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CameraBoomLength  = 200.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Weapon;*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Scabbard;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPlayerCombatComponent* PlayerCombatComponent;

#pragma endregion


	virtual void InitAbilityActorInfo() override;


public:
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent;}

	//void OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data);

protected:
	//FDelegateHandle MaxMovementSpeedChangedDelegateHandle;
	// Jump Ability with tags currently Broken Up Between the Player controller and this class
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer InAirTags;

	UFUNCTION(BlueprintCallable, Category = "OnCarMeleeAttack")
	FRotator GetMeleeRotationWarpTarget(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const;
};