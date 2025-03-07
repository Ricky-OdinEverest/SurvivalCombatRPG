// Copyright Ricky Everest


#include "AbilitySystem/SCR_AbilitySystemLibrary.h"

#include "Characters/Player/SCR_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/SCR_HUD.h"
#include "UI/WidgetController/SCR_WidgetController.h"

UOverlayWidgetController* USCR_AbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ASCR_HUD* SCR_HUD = Cast<ASCR_HUD>(PC->GetHUD()))
		{
			ASCR_PlayerState* PS = PC->GetPlayerState<ASCR_PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return SCR_HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* USCR_AbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ASCR_HUD* SCR_HUD = Cast<ASCR_HUD>(PC->GetHUD()))
		{
			ASCR_PlayerState* PS = PC->GetPlayerState<ASCR_PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return SCR_HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
