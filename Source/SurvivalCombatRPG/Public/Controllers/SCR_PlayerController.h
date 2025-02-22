// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SCR_PlayerController.generated.h"

class UDataAsset_InputConfig;
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
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:

#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);


#pragma endregion
};
