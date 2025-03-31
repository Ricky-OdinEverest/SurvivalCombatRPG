#include "AbilitySystem/AbilityTasks/SCR_EquipAbilityTask.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystem/Abilities/PlayerAbilities/SCR_PlayerGameplayAbility.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/SCR_PlayerWeaponBase.h" // Ensure this includes the full definition of your weapon class

USCR_EquipAbilityTask* USCR_EquipAbilityTask::Create_EquippedWeaponData(UGameplayAbility* OwningAbility)
{
    // Standard pattern for creating a new instance of an AbilityTask.
    USCR_EquipAbilityTask* MyObj = NewAbilityTask<USCR_EquipAbilityTask>(OwningAbility);
    return MyObj;
}

void USCR_EquipAbilityTask::Activate()
{
    Super::Activate();

    // Attempt to cast to your custom GameplayAbility.
    USCR_PlayerGameplayAbility* SCR_Ability = Cast<USCR_PlayerGameplayAbility>(Ability);
    if (!SCR_Ability)
    {
        EndTask();
        return;
    }

    // Retrieve the player combat component.
    UPlayerCombatComponent* PCC = SCR_Ability->GetPlayerCombatComponentFromActorInfo();
    if (!PCC)
    {
        EndTask();
        return;
    }

    // Example: Retrieve a weapon by its gameplay tag.
    ASCR_PlayerWeaponBase* FoundWeapon = PCC->GetPlayerCarriedWeaponByTag(FGameplayTag::RequestGameplayTag(TEXT("Player.Weapon.Sword")));

    // Check if this instance is locally controlled.
    const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
    if (bIsLocallyControlled)
    {
        // For locally controlled clients, immediately send the data.
        SendWeaponData(FoundWeapon, PCC);
    }
    else
    {
        // On the server, bind to the replicated data callback.
        const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
        const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
        AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey)
            .AddUObject(this, &USCR_EquipAbilityTask::OnTargetDataReplicatedCallback);

        const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
        if (!bCalledDelegate)
        {
            SetWaitingOnRemotePlayerData();
        }
    }
}

void USCR_EquipAbilityTask::SendWeaponData(ASCR_PlayerWeaponBase* InWeapon, UPlayerCombatComponent* InPCC)
{
    // Open a prediction window for client-to-server communication.
    FScopedPredictionWindow PredictionWindow(AbilitySystemComponent.Get(), true);

    // Create a handle and populate it with our custom target data struct.
    FGameplayAbilityTargetDataHandle DataHandle;
    FGameplayAbilityTargetData_Weapon* WeaponData = new FGameplayAbilityTargetData_Weapon();
    WeaponData->Weapon = InWeapon;
    WeaponData->PCC   = InPCC;

    DataHandle.Add(WeaponData);

    // Replicate the target data to the server.
    AbilitySystemComponent->ServerSetReplicatedTargetData(
        GetAbilitySpecHandle(),
        GetActivationPredictionKey(),
        DataHandle,
        FGameplayTag(), // Optional application tag.
        AbilitySystemComponent->ScopedPredictionKey
    );

    // Locally broadcast the data if the delegate should be triggered.
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnWeaponData.Broadcast(DataHandle);
    }
}

void USCR_EquipAbilityTask::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
    // Consume the replicated target data.
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

    // Broadcast the data to Blueprint or any listeners.
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnWeaponData.Broadcast(DataHandle);
    }
}

void USCR_EquipAbilityTask::OnDestroy(bool AbilityIsEnding)
{
    Super::OnDestroy(AbilityIsEnding);
}
