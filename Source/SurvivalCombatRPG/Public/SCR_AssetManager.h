// Copyright Ricky Everest

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SCR_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCOMBATRPG_API USCR_AssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static USCR_AssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
