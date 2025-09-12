// Copyright Ricky Everest


#include "SCR_MeleeBPFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "SCR_GameplayTags.h"
#include "SCR_DebugHelper.h"
#include "AbilitySystem/SCR_AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

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

void USCR_MeleeBPFunctionLibrary:: RemoveGameplayTagFromActorIfFound(AActor* InActor,FGameplayTag TagToRemove)
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

UPawnCombatComponent* USCR_MeleeBPFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
 
	if (ICombatInterface* PawnCombatInterface = Cast<ICombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
 
	return nullptr;
}

UPawnCombatComponent* USCR_MeleeBPFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	ESCR_ValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
 
	OutValidType = CombatComponent? ESCR_ValidType::Valid : ESCR_ValidType::Invalid;
 
	return CombatComponent;
}

bool USCR_MeleeBPFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

FGameplayTag USCR_MeleeBPFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
	float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward,VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward,VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference>=-45.f && OutAngleDifference <=45.f)
	{
		return SCR_GameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference<-45.f && OutAngleDifference>=-135.f)
	{
		return SCR_GameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference<-135.f || OutAngleDifference>135.f)
	{
		return SCR_GameplayTags::Shared_Status_HitReact_Back;
	}
	else if(OutAngleDifference>45.f && OutAngleDifference<=135.f)
	{
		return SCR_GameplayTags::Shared_Status_HitReact_Right;
	}

	return SCR_GameplayTags::Shared_Status_HitReact_Front;
}

bool USCR_MeleeBPFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	// Make sure both the attacker and defender actors are valid (not null).
	check(InAttacker && InDefender);

	// Compute the dot product of the attacker’s forward vector and defender’s forward vector.
	// - Each actor has a "forward vector", which is a unit vector pointing in the direction the actor is facing.
	// - The dot product between two normalized vectors gives:
	//     * +1 if they point in the exact same direction
	//     *  0 if they are perpendicular (90° apart)
	//     * -1 if they point in exactly opposite directions
	const float DotResult = FVector::DotProduct(
		InAttacker->GetActorForwardVector(), 
		InDefender->GetActorForwardVector()
	);

	// Create a debug string showing the dot product value and whether it’s considered a valid block.
	// - If DotResult < -0.1f, it means the defender is generally facing toward the attacker 
	//   (i.e., their forward vectors are pointing in opposite-ish directions).
	// - Otherwise, the defender is not facing the attacker enough to count as a block.
	/*const FString DebugString = FString::Printf(
		TEXT("Dot Result: %f %s"),
		DotResult,
		DotResult < -0.1f ? TEXT("Valid Block") : TEXT("Invalid Block")
	);*/

	// Print the debug string in the game world.
	// - If it’s a valid block (DotResult < -0.1f), print in green.
	// - Otherwise, print in red.
	//Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);

	// Return true if it’s a valid block, false otherwise.
	return DotResult < -0.1f ? true : false;

}
