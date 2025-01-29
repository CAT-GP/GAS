

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GAS_AttributeSet.h"
#include "GameplayEffectExtension.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include "Net/UnrealNetwork.h"

void UGAS_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxMovementSpeedAttribute())
	{
		ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningActor());

		UCharacterMovementComponent* CharacterMovement = OwningCharacter ? OwningCharacter->GetCharacterMovement() : nullptr;

		if (CharacterMovement)
		{
			const float maxSpeed = GetMaxMovementSpeed();
			CharacterMovement->MaxWalkSpeed = maxSpeed;
		}
	}
}

void UGAS_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Health, OldHealth);
}

void UGAS_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& MaxOldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, MaxHealth, MaxOldHealth);
}

void UGAS_AttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Stamina, OldStamina);
}

void UGAS_AttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& MaxOldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, MaxStamina, MaxOldStamina);
}

void UGAS_AttributeSet::OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, MaxMovementSpeed, OldMaxMovementSpeed);
}

void UGAS_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxMovementSpeed, COND_None, REPNOTIFY_Always);
}
