// Copyright Ricky Everest


#include "Characters/Enemy/SCR_Enemy.h"

#include "SCR_DebugHelper.h"
#include "Components/Combat/SCR_EnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
 #include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

ASCR_Enemy::ASCR_Enemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
 
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
 
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,180.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
 
	EnemyCombatComponent = CreateDefaultSubobject<USCR_EnemyCombatComponent>("EnemyCombatComponent");

}

UPawnCombatComponent* ASCR_Enemy::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}


void ASCR_Enemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void ASCR_Enemy::Die()
{
	EnemyCombatComponent->DropWeapon();
	Super::Die();
}

void ASCR_Enemy::InitEnemyStartUpData() const
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}
 
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(static_cast<USCR_AbilitySystemComponent*>(AbilitySystemComponent));


				}
			}
		)
		);
}
