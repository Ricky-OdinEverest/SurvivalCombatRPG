// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "SCR_PlayerController.generated.h"

class UInputAction;
class USCR_InputConfig;
class IEnemyInterface;

class USCR_AbilitySystemComponent;
class USplineComponent;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASCR_PlayerController();

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USCR_InputConfig> InputConfig;;

	UPROPERTY()
	TObjectPtr<USCR_AbilitySystemComponent> SCR_AbilitySystemComponent;

	USCR_AbilitySystemComponent* GetASC();

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;
	
	void ShiftPressed() { bShiftKeyDown = true; };
	void ShiftReleased() { bShiftKeyDown = false; };
	bool bShiftKeyDown = false;
	
	
	void CursorTrace();
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	FHitResult CursorHit;
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
 
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
 
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditAnywhere, Category = "MouseControl")
	bool bUsingMouse = false;
	
	void AutoRun();

	//UPROPERTY(EditAnywhere, Category="Input")
	//TObjectPtr<UInputAction> MoveAction;
 
	//void Move(const FInputActionValue& InputActionValue);
 
	
	
};


