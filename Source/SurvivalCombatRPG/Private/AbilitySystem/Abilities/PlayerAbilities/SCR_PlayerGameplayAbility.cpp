// Copyright Ricky Everest


#include "AbilitySystem/Abilities/PlayerAbilities/SCR_PlayerGameplayAbility.h"

#include "SCR_GameplayTags.h"
#include "Characters/Player/SCR_PlayerCharacter.h"
#include "Controllers/SCR_PlayerController.h"


ASCR_PlayerCharacter* USCR_PlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedSCRPlayerCharacter.IsValid())
	{
		CachedSCRPlayerCharacter = Cast<ASCR_PlayerCharacter>(CurrentActorInfo->AvatarActor);
	}
    
	return CachedSCRPlayerCharacter.IsValid()? CachedSCRPlayerCharacter.Get() : nullptr;
}

ASCR_PlayerController* USCR_PlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedSCRPlayerController.IsValid())
	{
		CachedSCRPlayerController = Cast<ASCR_PlayerController>(CurrentActorInfo->PlayerController);
	}
 
	return CachedSCRPlayerController.IsValid()? CachedSCRPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* USCR_PlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

FGameplayEffectSpecHandle USCR_PlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,float InWeaponBaseDamage,FGameplayTag InCurrentAttackTypeTag,int32 InUsedComboCount)
{
	check(EffectClass);
 
	FGameplayEffectContextHandle ContextHandle = GetPlayerAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(),GetAvatarActorFromActorInfo());
 
	FGameplayEffectSpecHandle EffectSpecHandle = GetPlayerAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);
 
	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		SCR_GameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);
 
	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag,InUsedComboCount);
	}
 
	return EffectSpecHandle;
}
