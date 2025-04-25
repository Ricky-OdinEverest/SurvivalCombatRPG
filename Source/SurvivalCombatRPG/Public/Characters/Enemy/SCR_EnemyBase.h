// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Characters/SCR_BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "SCR_EnemyBase.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class ASCR_AIController;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_EnemyBase : public ASCR_BaseCharacter,  public IEnemyInterface
{
	GENERATED_BODY()

public:
	ASCR_EnemyBase();
	virtual void PossessedBy(AController* NewController) override;

	virtual void HighlightActor() override;
	//UFUNCTION(BlueprintCallable)
	virtual void UnHighlightActor() override;

	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/** end Combat Interface */
	
	
 
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnBloodChanged;
 
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxBloodhChanged;
	
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
 
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;
 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;
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

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
 
	UPROPERTY()
	TObjectPtr<ASCR_AIController> SCR_AIController;


};
