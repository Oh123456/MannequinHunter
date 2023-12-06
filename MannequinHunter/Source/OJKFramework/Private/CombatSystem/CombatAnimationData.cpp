// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/CombatAnimationData.h"

UCombatAnimationData::UCombatAnimationData()
{
	
}

UCombatAnimationData::~UCombatAnimationData()
{
	combatMontageMap.Reset();
}

const FAnimMontageArray* UCombatAnimationData::GetMontageArray(const ECharacterCombatMontageType type) const
{
	return combatMontageMap.Find(type);
}

const UAnimMontage* UCombatAnimationData::GetMontage(const ECharacterCombatMontageType type, const int32 index) const
{
	FAnimMontageArray* montageArray = const_cast<FAnimMontageArray*>(GetMontageArray(type));
	UAnimMontage* montage = nullptr;
	if (montageArray)
	{
		if (montageArray->montages.Num() > index)
			montage = montageArray->montages[index];
	}

	return montage;
}
