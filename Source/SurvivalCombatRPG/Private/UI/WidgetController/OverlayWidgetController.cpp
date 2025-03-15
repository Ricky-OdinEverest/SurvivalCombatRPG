// Copyright Ricky Everest


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/SCR_AbilitySystemComponent.h"

#include "AbilitySystem/SCR_AttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const USCR_AttributeSet* SCR_AttributeSet = CastChecked<USCR_AttributeSet>(AttributeSet);
	
	// Blood Attributes
	OnBloodChanged.Broadcast(SCR_AttributeSet->GetBlood());
	OnMaxBloodChanged.Broadcast(SCR_AttributeSet->GetMaxBlood());

	// Mana Attributes
	OnManaChanged.Broadcast(SCR_AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(SCR_AttributeSet->GetMaxMana());

	// Stamina Attributes
	OnStaminaChanged.Broadcast(SCR_AttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(SCR_AttributeSet->GetMaxStamina());

	// Head Health Attributes
	OnHeadHealthChanged.Broadcast(SCR_AttributeSet->GetHeadHealth());
	OnMaxHeadHealthChanged.Broadcast(SCR_AttributeSet->GetMaxHeadHealth());

	// Chest Health Attributes
	OnChestHealthChanged.Broadcast(SCR_AttributeSet->GetChestHealth());
	OnMaxChestHealthChanged.Broadcast(SCR_AttributeSet->GetMaxChestHealth());

	// Stomach Health Attributes
	OnStomachHealthChanged.Broadcast(SCR_AttributeSet->GetStomachHealth());
	OnMaxStomachHealthChanged.Broadcast(SCR_AttributeSet->GetMaxStomachHealth());

	// Right Arm Health Attributes
	OnRightArmHealthChanged.Broadcast(SCR_AttributeSet->GetRightArmHealth());
	OnMaxRightArmHealthChanged.Broadcast(SCR_AttributeSet->GetMaxRightArmHealth());

	// Left Arm Health Attributes
	OnLeftArmHealthChanged.Broadcast(SCR_AttributeSet->GetLeftArmHealth());
	OnMaxLeftArmHealthChanged.Broadcast(SCR_AttributeSet->GetMaxLeftArmHealth());

	// Right Leg Health Attributes
	OnRightLegHealthChanged.Broadcast(SCR_AttributeSet->GetRightLegHealth());
	OnMaxRightLegHealthChanged.Broadcast(SCR_AttributeSet->GetMaxRightLegHealth());

	// Left Leg Health Attributes
	OnLeftLegHealthChanged.Broadcast(SCR_AttributeSet->GetLeftLegHealth());
	OnMaxLeftLegHealthChanged.Broadcast(SCR_AttributeSet->GetMaxLeftLegHealth());

	// Hunger Attributes
	OnHungerChanged.Broadcast(SCR_AttributeSet->GetHunger());
	OnMaxHungerChanged.Broadcast(SCR_AttributeSet->GetMaxHunger());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const USCR_AttributeSet* SCR_AttributeSet = CastChecked<USCR_AttributeSet>(AttributeSet);
	

	// Blood Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetBloodAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnBloodChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxBloodAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxBloodChanged.Broadcast(Data.NewValue);
		});

	// Mana Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		});

	// Stamina Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStaminaChanged.Broadcast(Data.NewValue);
		});

	// Head Health Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetHeadHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHeadHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxHeadHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHeadHealthChanged.Broadcast(Data.NewValue);
		});

	// Chest Health Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetChestHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnChestHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxChestHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxChestHealthChanged.Broadcast(Data.NewValue);
		});

	// Stomach Health Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetStomachHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStomachHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxStomachHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStomachHealthChanged.Broadcast(Data.NewValue);
		});

	// Right Arm Health Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetRightArmHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnRightArmHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxRightArmHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxRightArmHealthChanged.Broadcast(Data.NewValue);
		});

	// Left Arm Health Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetLeftArmHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnLeftArmHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxLeftArmHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxLeftArmHealthChanged.Broadcast(Data.NewValue);
		});

	// Right Leg Health Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetRightLegHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnRightLegHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxRightLegHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxRightLegHealthChanged.Broadcast(Data.NewValue);
		});

	// Left Leg Health Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetLeftLegHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnLeftLegHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxLeftLegHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxLeftLegHealthChanged.Broadcast(Data.NewValue);
		});

	// Hunger Attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetHungerAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHungerChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCR_AttributeSet->GetMaxHungerAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHungerChanged.Broadcast(Data.NewValue);
		});

	Cast<USCR_AbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			// For example, say that Tag = Message.HealthPotion 1
			// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}
	}
);
}

