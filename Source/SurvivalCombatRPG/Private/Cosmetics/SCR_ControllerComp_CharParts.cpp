// Copyright Ricky Everest


#include "Cosmetics/SCR_ControllerComp_CharParts.h"
#include "Cosmetics/SCR_CharacterPartTypes.h"
#include "Cosmetics/SCR_PawnComponent_CharacterParts.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SCR_ControllerComp_CharParts)

//////////////////////////////////////////////////////////////////////

USCR_ControllerComp_CharParts::USCR_ControllerComp_CharParts(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USCR_ControllerComp_CharParts::BeginPlay()
{
	Super::BeginPlay();

	// Listen for pawn possession changed events
	if (HasAuthority())
	{
		if (AController* OwningController = GetController<AController>())
		{
			OwningController->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::OnPossessedPawnChanged);

			if (APawn* ControlledPawn = GetPawn<APawn>())
			{
				OnPossessedPawnChanged(nullptr, ControlledPawn);
			}
		}
	}
}

void USCR_ControllerComp_CharParts::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveAllCharacterParts();
	Super::EndPlay(EndPlayReason);
}

USCR_PawnComponent_CharacterParts* USCR_ControllerComp_CharParts::GetPawnCustomizer() const
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		return ControlledPawn->FindComponentByClass<USCR_PawnComponent_CharacterParts>();
	}
	return nullptr;
}

void USCR_ControllerComp_CharParts::AddCharacterPart(const FSCR_CharacterPart& NewPart)
{
	AddCharacterPartInternal(NewPart, ECharacterPartSource::Natural);
}

void USCR_ControllerComp_CharParts::AddCharacterPartInternal(const FSCR_CharacterPart& NewPart, ECharacterPartSource Source)
{
	FSCR_ControllerCharacterPartEntry& NewEntry = CharacterParts.AddDefaulted_GetRef();
	NewEntry.Part = NewPart;
	NewEntry.Source = Source;

	if (USCR_PawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
	{
		if (NewEntry.Source != ECharacterPartSource::NaturalSuppressedViaCheat)
		{
			NewEntry.Handle = PawnCustomizer->AddCharacterPart(NewPart);
		}
	}

}

void USCR_ControllerComp_CharParts::RemoveCharacterPart(const FSCR_CharacterPart& PartToRemove)
{
	for (auto EntryIt = CharacterParts.CreateIterator(); EntryIt; ++EntryIt)
	{
		if (FSCR_CharacterPart::AreEquivalentParts(EntryIt->Part, PartToRemove))
		{
			if (USCR_PawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
			{
				PawnCustomizer->RemoveCharacterPart(EntryIt->Handle);
			}

			EntryIt.RemoveCurrent();
			break;
		}
	}
}

void USCR_ControllerComp_CharParts::RemoveAllCharacterParts()
{
	if (USCR_PawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
	{
		for (FSCR_ControllerCharacterPartEntry& Entry : CharacterParts)
		{
			PawnCustomizer->RemoveCharacterPart(Entry.Handle);
		}
	}

	CharacterParts.Reset();
}

void USCR_ControllerComp_CharParts::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	// Remove from the old pawn
	if (USCR_PawnComponent_CharacterParts* OldCustomizer = OldPawn ? OldPawn->FindComponentByClass<USCR_PawnComponent_CharacterParts>() : nullptr)
	{
		for (FSCR_ControllerCharacterPartEntry& Entry : CharacterParts)
		{
			OldCustomizer->RemoveCharacterPart(Entry.Handle);
			Entry.Handle.Reset();
		}
	}

	// Apply to the new pawn
	if (USCR_PawnComponent_CharacterParts* NewCustomizer = NewPawn ? NewPawn->FindComponentByClass<USCR_PawnComponent_CharacterParts>() : nullptr)
	{
		for (FSCR_ControllerCharacterPartEntry& Entry : CharacterParts)
		{
			// Don't readd if it's already there, this can get called with a null oldpawn
			if (!Entry.Handle.IsValid() && Entry.Source != ECharacterPartSource::NaturalSuppressedViaCheat)
			{
				Entry.Handle = NewCustomizer->AddCharacterPart(Entry.Part);
			}
		}
	}
}
