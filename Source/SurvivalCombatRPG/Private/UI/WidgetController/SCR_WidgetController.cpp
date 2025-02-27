// Copyright Ricky Everest


#include "UI/WidgetController/SCR_WidgetController.h"

void USCR_WidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void USCR_WidgetController::BroadcastInitialValues()
{
}

void USCR_WidgetController::BindCallbacksToDependencies()
{
}
