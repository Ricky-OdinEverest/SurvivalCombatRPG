// Copyright Ricky Everest


#include "UI/Widgets/SCR_UserWidget.h"

void USCR_UserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
