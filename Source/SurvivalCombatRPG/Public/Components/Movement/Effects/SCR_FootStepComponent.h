// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCR_FootStepComponent.generated.h"

enum class EFoot : uint8;
class SCR_ParkourEnumTypes;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCOMBATRPG_API USCR_FootStepComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USCR_FootStepComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	FName LeftFootSocketName = TEXT("foot_l");

	UPROPERTY(EditDefaultsOnly)
	FName RightFootSocketName = TEXT("foot_r");

public:	

	void HandleFootstep(EFoot Foot);
		
};
