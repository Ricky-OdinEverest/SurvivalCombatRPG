// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"

#include "DataAssets/Input/SCR_InputConfig.h"
#include "SCR_EInputComponent.generated.h"

/**
 * @class USCR_EInputComponent
 * @brief An extended version of the UEnhancedInputComponent.
 *
 * This custom input component is designed to streamline the process of binding input actions
 * defined in a USCR_InputConfig data asset. It provides templated helper functions to bind
 * actions to gameplay abilities and native functions using GameplayTags, reducing boilerplate code.
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_EInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Binds pressed, released, and held events for all ability actions defined in the InputConfig.
	 * @tparam UserClass The type of the object that owns the functions to be bound (e.g., APlayerController, UCharacterMovementComponent).
	 * @tparam PressedFuncType The type of the function to call when an action is pressed (Started event).
	 * @tparam ReleasedFuncType The type of the function to call when an action is released (Completed event).
	 * @tparam HeldFuncType The type of the function to call when an action is held (Triggered event).
	 * @param InputConfig A pointer to the data asset containing the input action configurations.
	 * @param Object The object instance on which the callback functions will be called.
	 * @param PressedFunc The function to bind to the ETriggerEvent::Started event.
	 * @param ReleasedFunc The function to bind to the ETriggerEvent::Completed event.
	 * @param HeldFunc The function to bind to the ETriggerEvent::Triggered event.
	 */
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
