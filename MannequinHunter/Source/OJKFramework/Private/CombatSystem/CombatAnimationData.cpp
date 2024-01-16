// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/CombatAnimationData.h"

UCombatAnimationData::UCombatAnimationData()
{
	
}

UCombatAnimationData::~UCombatAnimationData()
{
	combatMontageMap.Reset();
}

const TArray<UAnimMontage*>* UCombatAnimationData::GetMontageArray(const ECharacterCombatMontageType type) const
{
	const FAnimMontageArray* montageArray = combatMontageMap.Find(type);

	if (montageArray == nullptr)
		return nullptr;

	return &montageArray->montages;
}