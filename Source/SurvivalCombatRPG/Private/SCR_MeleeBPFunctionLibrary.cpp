// Copyright Ricky Everest


#include "SCR_MeleeBPFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"

USCR_AbilitySystemComponent* USCR_MeleeBPFunctionLibrary::NativeGetSCR_ASCFromActor(AActor* InActor)
{
	check(InActor);
 
	return CastChecked<USCR_AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void USCR_MeleeBPFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	USCR_AbilitySystemComponent* ASC = NativeGetSCR_ASCFromActor(InActor);
 
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void USCR_MeleeBPFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	USCR_AbilitySystemComponent* ASC = NativeGetSCR_ASCFromActor(InActor);
 
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool USCR_MeleeBPFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	USCR_AbilitySystemComponent* ASC = NativeGetSCR_ASCFromActor(InActor);
 
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void USCR_MeleeBPFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
	ESCR_ConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor,TagToCheck)? ESCR_ConfirmType::Yes : ESCR_ConfirmType::No;
}
