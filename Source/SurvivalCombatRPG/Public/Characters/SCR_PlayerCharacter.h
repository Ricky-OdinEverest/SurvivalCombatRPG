// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Characters/SCR_BaseCharacter.h"
#include "SCR_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_PlayerCharacter : public ASCR_BaseCharacter
{
	GENERATED_BODY()

public:
	ASCR_PlayerCharacter();
	
protected:
	virtual void BeginPlay() override;

private:

#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

#pragma endregion
	
};