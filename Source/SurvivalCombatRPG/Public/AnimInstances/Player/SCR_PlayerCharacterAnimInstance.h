// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/SCR_CharacterAnimInstance.h"
#include "SCR_PlayerCharacterAnimInstance.generated.h"

class ASCR_PlayerCharacter;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_PlayerCharacterAnimInstance : public USCR_CharacterAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	
	// Getter to access the player-specific character.
	UFUNCTION(BlueprintCallable, Category = "AnimData|References")
	ASCR_PlayerCharacter* GetPlayerCharacter() const;
};


