

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GAS_AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UGAS_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
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

void UGAS_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}
