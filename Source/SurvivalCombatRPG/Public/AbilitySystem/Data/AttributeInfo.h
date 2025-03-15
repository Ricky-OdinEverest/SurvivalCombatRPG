// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FSCR_AttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute AttributeToGet;
};

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	FSCR_AttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;
#if WITH_EDITOR
	UFUNCTION(Category="Populate Attribute Info", CallInEditor)
	void PopulateDataAsset();
#endif
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty="{AttributeName}"))
	TArray<FSCR_AttributeInfo> AttributeInformation;
};