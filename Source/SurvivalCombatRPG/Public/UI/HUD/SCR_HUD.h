// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SCR_HUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;
class USCR_UserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API ASCR_HUD : public AHUD
{
	GENERATED_BODY()
public:


	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);



private:

	UPROPERTY()
	TObjectPtr<USCR_UserWidget>  OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USCR_UserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};