// Copyright Ricky Everest

#pragma once

#include "SCR_CharacterPartTypes.h"
#include "Components/ControllerComponent.h"
#include "SCR_ControllerComp_CharParts.generated.h"

class APawn;
class USCR_PawnComponent_CharacterParts;
class UObject;
struct FFrame;

enum class ECharacterPartSource : uint8
{
	Natural,

	NaturalSuppressedViaCheat,

	AppliedViaDeveloperSettingsCheat,

	AppliedViaCheatManager
};

//////////////////////////////////////////////////////////////////////

// A character part requested on a controller component

USTRUCT()
struct FSCR_ControllerCharacterPartEntry
{
	GENERATED_BODY()

	FSCR_ControllerCharacterPartEntry()
	{}

public:
	// The character part being represented
	UPROPERTY(EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSCR_CharacterPart Part;

	// The handle if already applied to a pawn
	FSCR_CharacterPartHandle Handle;

	// The source of this part
	ECharacterPartSource Source = ECharacterPartSource::Natural;
};
//////////////////////////////////////////////////////////////////////

// A component that configure what cosmetic actors to spawn for the owning controller when it possesses a pawn
UCLASS(meta = (BlueprintSpawnableComponent))
class SURVIVALCOMBATRPG_API USCR_ControllerComp_CharParts : public UControllerComponent
{
	GENERATED_BODY()
public:
	USCR_ControllerComp_CharParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of UActorComponent interface

	// Adds a character part to the actor that owns this customization component, should be called on the authority only
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Cosmetics)
	void AddCharacterPart(const FSCR_CharacterPart& NewPart);

	// Removes a previously added character part from the actor that owns this customization component, should be called on the authority only
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Cosmetics)
	void RemoveCharacterPart(const FSCR_CharacterPart& PartToRemove);

	// Removes all added character parts, should be called on the authority only
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Cosmetics)
	void RemoveAllCharacterParts();


protected:
	UPROPERTY(EditAnywhere, Category=Cosmetics)
	TArray<FSCR_ControllerCharacterPartEntry> CharacterParts;

private:
	USCR_PawnComponent_CharacterParts* GetPawnCustomizer() const;

	UFUNCTION()
	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

	void AddCharacterPartInternal(const FSCR_CharacterPart& NewPart, ECharacterPartSource Source);

};
