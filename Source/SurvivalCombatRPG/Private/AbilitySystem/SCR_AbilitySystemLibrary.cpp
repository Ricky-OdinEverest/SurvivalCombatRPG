// Copyright Ricky Everest


#include "AbilitySystem/SCR_AbilitySystemLibrary.h"

#include "SCR_AbilityTypes.h"
#include "Characters/Player/SCR_PlayerState.h"
#include "GameModes/SCR_GameModeBase.h"
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

void USCR_AbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
 
	if (UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject))
	{
		FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
 
		FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext(); 
		PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
 
		FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
		SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
 
		FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
		VitalAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
	}
	else
	{
		return;
	}
}

void USCR_AbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	if(UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject))
	{
		for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
			ASC->GiveAbility(AbilitySpec);
		}
	}
	else
	{
		return;
	}
}

UCharacterClassInfo* USCR_AbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{

	ASCR_GameModeBase* SCR_GameModeBase = Cast<ASCR_GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (SCR_GameModeBase == nullptr) return nullptr;
	return SCR_GameModeBase->CharacterClassInfo;
}

bool USCR_AbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	
	if (const FSCR_GameplayEffectContext* SCR_GameplayEffectContext = static_cast<const FSCR_GameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return SCR_GameplayEffectContext->IsCriticalHit();
	}
	return false;
}

void USCR_AbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FSCR_GameplayEffectContext* SCR_GameplayEffectContext = static_cast<FSCR_GameplayEffectContext*>(EffectContextHandle.Get()))
	{
		SCR_GameplayEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}
