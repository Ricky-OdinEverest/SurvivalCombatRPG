#include "AbilitySystem/AbilityTasks/SCR_EquipAbilityTask.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystem/Abilities/PlayerAbilities/SCR_PlayerGameplayAbility.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/SCR_PlayerWeaponBase.h" // Make sure you include whichever header defines your weapon class

USCR_EquipAbilityTask* USCR_EquipAbilityTask::Create_EquippedWeaponData(UGameplayAbility* OwningAbility)
{
    // Standard pattern for creating a new instance of an AbilityTask
    USCR_EquipAbilityTask* MyObj = NewAbilityTask<USCR_EquipAbilityTask>(OwningAbility);
    return MyObj;
}

void USCR_EquipAbilityTask::Activate()
{
    Super::Activate();

    
    // Try to cast to your custom GameplayAbility
    USCR_PlayerGameplayAbility* SCR_Ability = Cast<USCR_PlayerGameplayAbility>(Ability);
    if (!SCR_Ability)
    {
        EndTask();
        return;
    }

    // Grab the player combat component
    UPlayerCombatComponent* PCC = SCR_Ability->GetPlayerCombatComponentFromActorInfo();
    if (!PCC)
    {
        EndTask();
        return;
    }

    // For example, we get a "Sword" weapon by tag.
    // Adjust function name or param to match your code base:
    ASCR_PlayerWeaponBase* FoundWeapon = PCC->GetPlayerCarriedWeaponByTag(
        FGameplayTag::RequestGameplayTag(TEXT("Player.Weapon.Sword"))
    );

    // Now replicate the weapon pointer to the server and other clients
    // using the "SendWeaponData" pattern
    
    const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
    if (bIsLocallyControlled)
    {
        // Pass both the FoundWeapon and the PCC
        SendWeaponData(FoundWeapon, PCC);
    }
    else
    {
        //TODO: We are on the server, so listen for target data.
        const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
        const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
        AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &USCR_EquipAbilityTask::OnTargetDataReplicatedCallback);
        const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
        if (!bCalledDelegate)
        {
            SetWaitingOnRemotePlayerData();
        }
    }
}

void USCR_EquipAbilityTask::SendWeaponData(ASCR_PlayerWeaponBase* InWeapon, UPlayerCombatComponent* InPCC)
{

    // Open a prediction window if doing client->server
    // So the server accepts the replicated data for this ability activation
    FScopedPredictionWindow PredictionWindow(AbilitySystemComponent.Get(), true);

    // 1) Create a handle and populate it with our custom struct
    FGameplayAbilityTargetDataHandle DataHandle;
    // Allocate our custom struct on the heap
    FGameplayAbilityTargetData_Weapon* WeaponData = new FGameplayAbilityTargetData_Weapon();
    WeaponData->Weapon = InWeapon;
    WeaponData->PCC   = InPCC;  // <-- store the combat component pointer

    DataHandle.Add(WeaponData);

    // 2) Replicate to the Server so it can validate or pass it along
    AbilitySystemComponent->ServerSetReplicatedTargetData(
        GetAbilitySpecHandle(),
        GetActivationPredictionKey(),
        DataHandle,
        /* Optional application tag: */ FGameplayTag(),
        AbilitySystemComponent->ScopedPredictionKey
    );

    // 3) Locally broadcast. If you’re on the client, you can respond immediately
    //    If you’re on the server, this also triggers for your server logic or dedicated server.
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnWeaponData.Broadcast(DataHandle);
    }

}

void USCR_EquipAbilityTask::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag) const
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnWeaponData.Broadcast(DataHandle);
    }
}

