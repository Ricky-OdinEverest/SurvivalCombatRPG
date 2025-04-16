#pragma once
#include "GameplayEffectTypes.h"
#include "SCR_AbilityTypes.generated.h"
 
USTRUCT(BlueprintType)
struct FSCR_GameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
 
public:
 
	bool IsCriticalHit() const { return bIsCriticalHit; }
	/*bool IsBlockedHit () const { return bIsBlockedHit; }*/
 
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	/*void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }*/
 	
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}
	
	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FSCR_GameplayEffectContext* Duplicate() const
	{
		FSCR_GameplayEffectContext* NewContext = new FSCR_GameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
 
	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
 	
protected:
 
	/*
	UPROPERTY()
	bool bIsBlockedHit = false;*/
 	
	UPROPERTY()
	bool bIsCriticalHit = false;
 	
};

template<>
 struct TStructOpsTypeTraits<FSCR_GameplayEffectContext> : public TStructOpsTypeTraitsBase2<FSCR_GameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

