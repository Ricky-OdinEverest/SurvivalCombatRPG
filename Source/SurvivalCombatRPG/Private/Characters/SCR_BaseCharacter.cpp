// Copyright Ricky Everest


#include "Characters/SCR_BaseCharacter.h"

// Sets default values
ASCR_BaseCharacter::ASCR_BaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

}