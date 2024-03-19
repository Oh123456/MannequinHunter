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

const FAnimSlotData* UCombatAnimationData::GetSlotData(const ECharacterCombatMontageType type) const
{
	return combatMontageMap.Find(type);
}

void UCombatAnimationData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (GET_MEMBER_NAME_CHECKED(UCombatAnimationData, combatMontageMap) != PropertyChangedEvent.Property->GetFName())
		return;

	combatMontageMap.KeySort([](ECharacterCombatMontageType data1, ECharacterCombatMontageType data2) 
		{
			return data1 < data2;
		});
}
