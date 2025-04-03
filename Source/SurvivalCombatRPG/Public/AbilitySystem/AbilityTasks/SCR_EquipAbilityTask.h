
#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/Abilities/SCR_AbilityTypes.h" // Include the new header
#include "SCR_EquipAbilityTask.generated.h"


class UEnhancedInputLocalPlayerSubsystem;
UCLASS()
class USCR_EquipAbilityTask : public UAbilityTask
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (DisplayName = "SCR_WeaponSwitchMappingContext",HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static USCR_EquipAbilityTask* SwitchMappingContext(UGameplayAbility* OwningAbility, UInputMappingContext* NewMappingContext, int32 Priority = 1);
	
	virtual void Activate() override;
	
	UFUNCTION(Client, Reliable)
	void Client_SwitchMappingContext(UInputMappingContext* NewMappingContext, int32 InPriority);
	
private:
	UPROPERTY()
	UInputMappingContext* MappingContext;
	
	int32 Priority;
};