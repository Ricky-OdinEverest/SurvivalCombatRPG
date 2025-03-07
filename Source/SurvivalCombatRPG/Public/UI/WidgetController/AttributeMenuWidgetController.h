// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SCR_WidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FSCR_AttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)

class SURVIVALCOMBATRPG_API UAttributeMenuWidgetController : public USCR_WidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

	
private:

	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;

};
