// Copyright Ricky Everest


#include "Animation/SCR_Step_AnimNotify.h"
#include "Characters/SCR_BaseCharacter.h"

#include "Components/Movement/Effects/SCR_FootStepComponent.h"

void USCR_Step_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	check(MeshComp);  
  
	ASCR_BaseCharacter* Character = MeshComp ? Cast<ASCR_BaseCharacter>(MeshComp->GetOwner()) : nullptr;  
	if (Character)  
	{
		if (USCR_FootStepComponent* FootstepsComponent = Character->GetFootstepsComponent())
		{
			FootstepsComponent->HandleFootstep(Foot);
		}
	}
}

