// Copyright Ricky Everest

#include "AbilitySystem/AbilityTasks/FindTargetFromPlayer.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"


UFindTargetFromPlayer* UFindTargetFromPlayer::CreateTargetFromPlayer(UGameplayAbility* OwningAbility)
{
	UFindTargetFromPlayer* MyObj = NewAbilityTask<UFindTargetFromPlayer>(OwningAbility);
	return MyObj;
}

void UFindTargetFromPlayer::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendAimData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UFindTargetFromPlayer::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UFindTargetFromPlayer::SendAimData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

   // Obtain the player controller and camera component
   APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	APlayerCameraManager* CamManager = PC->PlayerCameraManager;

	// Camera location and rotation
	FVector CameraLocation = CamManager->GetCameraLocation();
	FRotator CameraRotation = CamManager->GetCameraRotation();
	
	// Trace outward from camera
	FVector End = CameraLocation + (CameraRotation.Vector() * 10000.f);

   FHitResult TraceHit;
   FCollisionQueryParams QueryParams;
   QueryParams.AddIgnoredActor(Ability->GetCurrentActorInfo()->AvatarActor.Get());

	// Perform the line trace
	GetWorld()->LineTraceSingleByChannel(TraceHit, CameraLocation, End, ECC_Visibility, QueryParams);


	if(TraceHit.bBlockingHit)
	{
		/*GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *TraceHit.GetActor()->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Impact Point: %s"), *TraceHit.ImpactPoint.ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Normal Point: %s"), *TraceHit.ImpactNormal.ToString()));*/
	}
	else if (!TraceHit.bBlockingHit)
	{
		TraceHit.Location = End;
	}
   // Build the target data from the trace hit result
   FGameplayAbilityTargetDataHandle DataHandle;
   FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
   Data->HitResult = TraceHit;
   DataHandle.Add(Data);
	

   // Replicate the target data to the server
   AbilitySystemComponent->ServerSetReplicatedTargetData(
	   GetAbilitySpecHandle(),
	   GetActivationPredictionKey(),
	   DataHandle,
	   FGameplayTag(),
	   AbilitySystemComponent->ScopedPredictionKey);

   // Broadcast the valid data if needed
   if (ShouldBroadcastAbilityTaskDelegates())
   {
	   ValidData.Broadcast(DataHandle);
   }

}

void UFindTargetFromPlayer::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
