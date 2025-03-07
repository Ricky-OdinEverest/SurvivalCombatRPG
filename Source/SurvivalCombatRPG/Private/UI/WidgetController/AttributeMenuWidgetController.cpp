// Copyright Ricky Everest


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "SCR_GameplayTags.h"
#include "AbilitySystem/SCR_AttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"



void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	USCR_AttributeSet* AS = CastChecked<USCR_AttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
	);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	USCR_AttributeSet* AS = CastChecked<USCR_AttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FSCR_AttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
