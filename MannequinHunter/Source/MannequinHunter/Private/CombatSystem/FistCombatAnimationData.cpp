// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/FistCombatAnimationData.h"
#include "Equipment/FistWeapon.h"

const TArray<FFistAnimMontageHitBoxFlagArray>* UFistCombatAnimationData::GetHitBoxSlotFlag(const ECharacterCombatMontageType type)
{
	const FFistAnimMontageArray* montageArray = combatMontageMap.Find(type);

	if (montageArray == nullptr)
		return nullptr;

	return &(montageArray->montageFlag);
}

const TArray<UAnimMontage*>* UFistCombatAnimationData::GetMontageArray(const ECharacterCombatMontageType type) const
{
	const FFistAnimMontageArray* montageArray = combatMontageMap.Find(type);

	if (montageArray == nullptr)
		return nullptr;

	return &montageArray->montages;
}

const FAnimSlotData* UFistCombatAnimationData::GetSlotData(const ECharacterCombatMontageType type) const
{
	return combatMontageMap.Find(type);
}

void UFistCombatAnimationData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (GET_MEMBER_NAME_CHECKED(UFistCombatAnimationData, combatMontageMap) != PropertyChangedEvent.Property->GetFName())
		return;

	combatMontageMap.KeySort([](ECharacterCombatMontageType data1, ECharacterCombatMontageType data2)
		{
			return data1 < data2;
		});
}
