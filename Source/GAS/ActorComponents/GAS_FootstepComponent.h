// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GAS_GameTypes.h"
#include "GAS_FootstepComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_API UGAS_FootstepComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGAS_FootstepComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	FName LeftFootSocket = TEXT("foot_l");

	UPROPERTY(EditDefaultsOnly)
	FName RightFootSocket = TEXT("foot_r");

public:
	void HandleFootstep(EFoot Foot);

	
};
