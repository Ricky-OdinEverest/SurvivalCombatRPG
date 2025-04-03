#include "AbilitySystem/AbilityTasks/SCR_EquipAbilityTask.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystem/Abilities/PlayerAbilities/SCR_PlayerGameplayAbility.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/SCR_PlayerWeaponBase.h" // Ensure this includes the full definition of your weapon class


USCR_EquipAbilityTask* USCR_EquipAbilityTask::SwitchMappingContext(UGameplayAbility* OwningAbility,
    UInputMappingContext* NewMappingContext, int32 Priority)
{
    USCR_EquipAbilityTask* MyTask = NewAbilityTask<USCR_EquipAbilityTask>(OwningAbility);
    MyTask->MappingContext = NewMappingContext;
    MyTask->Priority = Priority;
    return MyTask;
}

void USCR_EquipAbilityTask::Activate()
{
    if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
    {
        Client_SwitchMappingContext(MappingContext, Priority);
    }
    
    EndTask();

}

void USCR_EquipAbilityTask::Client_SwitchMappingContext_Implementation(UInputMappingContext* NewMappingContext, int32 InPriority)
{
    if (APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get())
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            InputSubsystem->AddMappingContext(NewMappingContext, InPriority);
        }
    }
}

