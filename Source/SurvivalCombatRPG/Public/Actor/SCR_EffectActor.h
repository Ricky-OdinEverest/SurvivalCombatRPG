// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCR_EffectActor.generated.h"

class USphereComponent;
class UGameplayEffect;

UCLASS()
class SURVIVALCOMBATRPG_API ASCR_EffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ASCR_EffectActor();


protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

};
