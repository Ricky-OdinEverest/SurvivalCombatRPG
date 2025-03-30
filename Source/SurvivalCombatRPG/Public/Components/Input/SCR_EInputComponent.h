// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"

#include "DataAssets/Input/SCR_InputConfig.h"
#include "SCR_EInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_EInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	 void BindAbilityActions(const USCR_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

	template<class UserObject,typename CallbackFunc>
 void BindNativeInputAction(const USCR_InputConfig* InInputConfig,const FGameplayTag& InInputTag,ETriggerEvent TriggerEvent,UserObject* ContextObject,CallbackFunc Func);
	
	template<class UserObject,typename CallbackFunc>
	 void BindAbilityInputAction(const USCR_InputConfig* InInputConfig,UserObject* ContextObject,CallbackFunc InputPressedFunc,CallbackFunc InputRelasedFunc);

};





template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
 void USCR_EInputComponent::BindAbilityActions(const USCR_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
 
	for (const FSCR_InputActionConfig& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
 
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
 			
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}



template <class UserObject, typename CallbackFunc>
void USCR_EInputComponent::BindNativeInputAction(const USCR_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
	ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig,TEXT("Input config data asset is null,can not proceed with binding"));
 
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction,TriggerEvent,ContextObject,Func);
	}
}

template <class UserObject, typename CallbackFunc>
void USCR_EInputComponent::BindAbilityInputAction(const USCR_InputConfig* InInputConfig, UserObject* ContextObject,
	CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc)
{
	checkf(InInputConfig,TEXT("Input config data asset is null,can not proceed with binding"));
 
	for (const FSCR_InputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if(!AbilityInputActionConfig.IsValid()) continue;
 
		BindAction(AbilityInputActionConfig.InputAction,ETriggerEvent::Started,ContextObject,InputPressedFunc,AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction,ETriggerEvent::Completed,ContextObject,InputRelasedFunc,AbilityInputActionConfig.InputTag);
	}
}
