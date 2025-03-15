// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
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

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
