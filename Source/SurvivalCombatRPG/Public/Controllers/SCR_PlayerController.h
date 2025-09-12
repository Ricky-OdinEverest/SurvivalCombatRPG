// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "SCR_PlayerController.generated.h"

class UInputAction;
class USCR_InputConfig;
class IEnemyInterface;
class UDamageTextComponent;
class USCR_AbilitySystemComponent;
class USplineComponent;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_PlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	ASCR_PlayerController();

	
	//~ Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface


	virtual void PlayerTick(float DeltaTime) override;
	
		
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bCriticalHit);
	
	
	UFUNCTION(BlueprintCallable)
	void ShowMagicCircle(UMaterialInterface* DecalMaterial = nullptr);

	UFUNCTION(BlueprintCallable)
	void HideMagicCircle();


	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SendGameplayEventToSelf(const FGameplayTag& EventTag, const FGameplayEventData& EventData);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	
	// Blueprint callable getter for the Enhanced Input Local Player Subsystem
	UFUNCTION(BlueprintCallable, Category = "Input")
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;

	

private:
	FGenericTeamId HeroTeamID;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USCR_InputConfig> InputConfig;


	UPROPERTY()
	TObjectPtr<USCR_AbilitySystemComponent> SCR_AbilitySystemComponent;

	USCR_AbilitySystemComponent* GetASC();

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	FVector2D SwitchDirection = FVector2D::ZeroVector;

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

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	//UPROPERTY(EditAnywhere, Category="Input")
	//TObjectPtr<UInputAction> MoveAction;
 
	//void Move(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMagicCircle> MagicCircleClass;

	UPROPERTY()
	TObjectPtr<AMagicCircle> MagicCircle;

	void UpdateMagicCircleLocation();
protected:
	// Experiment Event tag to Trigger Jump Ability
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag JumpEventTag;
	
	
	
};


