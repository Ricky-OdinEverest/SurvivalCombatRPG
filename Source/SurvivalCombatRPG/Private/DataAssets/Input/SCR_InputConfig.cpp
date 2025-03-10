// Copyright Ricky Everest


#include "DataAssets/Input/SCR_InputConfig.h"


// Formerly Native input Action
UInputAction* USCR_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FSCR_InputActionConfig& InputActionConfig : AbilityInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
