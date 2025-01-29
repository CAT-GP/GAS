// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_Step.h"
#include "GASCharacter.h"
#include "ActorComponents/GAS_FootstepComponent.h"

void UAnimNotify_Step::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	check(MeshComp);

	AGASCharacter* Character = MeshComp ? Cast<AGASCharacter>(MeshComp->GetOwner()) : nullptr;

	if (Character)
	{
		if (UGAS_FootstepComponent* FootstepsComp = Character->GetFootstepsComponent())
		{
			FootstepsComp->HandleFootstep(Foot);
		}
	}
}
