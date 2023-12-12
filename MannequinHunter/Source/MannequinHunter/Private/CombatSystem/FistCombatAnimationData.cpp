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
