// Copyright Ricky Everest


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/SCR_AttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const USCR_AttributeSet* SCR_AttributeSet = CastChecked<USCR_AttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(SCR_AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(SCR_AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(SCR_AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(SCR_AttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const USCR_AttributeSet* SCR_AttributeSet = CastChecked<USCR_AttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SCR_AttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SCR_AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	SCR_AttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SCR_AttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
