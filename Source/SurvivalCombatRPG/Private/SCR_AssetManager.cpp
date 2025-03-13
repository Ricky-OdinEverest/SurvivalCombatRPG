// Copyright Ricky Everest


#include "SCR_AssetManager.h"
#include "AbilitySystemGlobals.h"
#include "SCR_GameplayTags.h"

USCR_AssetManager& USCR_AssetManager::Get()
{
	check(GEngine);
	
	USCR_AssetManager* SCR_AssetManager = Cast<USCR_AssetManager>(GEngine->AssetManager);
	return *SCR_AssetManager;
}

void USCR_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FSCR_GameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
