// Copyright Ricky Everest


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "SCR_GameplayTags.h"
#include "AbilitySystem/SCR_AttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"



void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	USCR_AttributeSet* AS = CastChecked<USCR_AttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (FSCR_AttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeToGet).AddLambda(
		[this, Info](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Info.AttributeTag);
		}
	);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	USCR_AttributeSet* AS = CastChecked<USCR_AttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for (FSCR_AttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		BroadcastAttributeInfo(Info.AttributeTag);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfoOrg(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FSCR_AttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag) const
{
//getting info from Data Asset Attribute Info based on Gameplay Tag
	FSCR_AttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag);
	//Set Hidden Value in AttributeInfo Data Asset
	Info.AttributeValue = Info.AttributeToGet.GetNumericValue(AttributeSet);
	//Broadcast for those who subscribe. IE the attribute menu widget in blueprint
	AttributeInfoDelegate.Broadcast(Info);
}
