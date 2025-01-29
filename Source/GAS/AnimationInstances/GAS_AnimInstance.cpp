// Fill out your copyright notice in the Description page of Project Settings.

#include "GASCharacter.h"
#include "GAS_GameTypes.h"

#include "Animation/AnimSequenceBase.h"
#include "Animation/BlendSpace.h"

#include "DataAssets/CharacterDataAsset.h"
#include "DataAssets/CharacterAnimationDataAsset.h"

#include "AnimationInstances/GAS_AnimInstance.h"

UBlendSpace* UGAS_AnimInstance::GetLocomotionBlendSpace() const
{
	if (AGASCharacter* GasCharacter = Cast<AGASCharacter>(GetOwningActor()))
	{
		FCharacterData Data = GasCharacter->GetCharacterData();

		if (Data.CharacterAnimationDataAsset)
		{
			return Data.CharacterAnimationDataAsset->CharacterAnimationData.MovementBlendSpace;
		}
	}

	return nullptr;
}

UAnimSequenceBase* UGAS_AnimInstance::GetIdleAnimation() const
{
	if (AGASCharacter* GasCharacter = Cast<AGASCharacter>(GetOwningActor()))
	{
		FCharacterData Data = GasCharacter->GetCharacterData();

		if (Data.CharacterAnimationDataAsset)
		{
			return Data.CharacterAnimationDataAsset->CharacterAnimationData.IdleAnimationAsset;
		}
	}

	return nullptr;
}
