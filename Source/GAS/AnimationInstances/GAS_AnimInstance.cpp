// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimationInstances/GAS_AnimInstance.h"

#include "GASCharacter.h"
#include "GAS_GameTypes.h"

#include "Animation/AnimSequenceBase.h"
#include "Animation/BlendSpace.h"

#include "DataAssets/CharacterDataAsset.h"
#include "DataAssets/CharacterAnimationDataAsset.h"


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

	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.MovementBlendSpace : nullptr;
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

	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset : nullptr;
}
