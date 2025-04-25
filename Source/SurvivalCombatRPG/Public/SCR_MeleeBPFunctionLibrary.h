// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SCR_MeleeEnumTypes.h"
#include "SCR_MeleeBPFunctionLibrary.generated.h"


class USCR_AbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_MeleeBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static USCR_AbilitySystemComponent* NativeGetSCR_ASCFromActor(AActor* InActor);
 
	UFUNCTION(BlueprintCallable, Category = "SCR_Melee|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor,FGameplayTag TagToAdd);
 
	UFUNCTION(BlueprintCallable, Category = "SCR_Melee|FunctionLibrary")
	static void RemoveGameplayFromActorIfFound(AActor* InActor,FGameplayTag TagToRemove);
 
	static bool NativeDoesActorHaveTag(AActor* InActor,FGameplayTag TagToCheck);
 
	UFUNCTION(BlueprintCallable, Category = "SCR_Melee|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor,FGameplayTag TagToCheck,ESCR_ConfirmType& OutConfirmType);
	
	
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);
 
	UFUNCTION(BlueprintCallable, Category = "SCR_Melee|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor,ESCR_ValidType& OutValidType);
	
};
