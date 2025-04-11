// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Characters/SCR_BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "SCR_EnemyBase.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_EnemyBase : public ASCR_BaseCharacter,  public IEnemyInterface
{
	GENERATED_BODY()

public:
	ASCR_EnemyBase();

	virtual void HighlightActor() override;
	//UFUNCTION(BlueprintCallable)
	virtual void UnHighlightActor() override;

	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnBloodChanged;
 
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxBloodhChanged;
	
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
 
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;
 
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
