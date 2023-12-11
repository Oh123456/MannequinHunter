// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/FistCombatAnimationData.h"
#include "Equipment/FistWeapon.h"

EFistWeaponSlotFlag UFistCombatAnimationData::GetHitBoxSlotFlag(const ECharacterCombatMontageType type)
{
	const FFistAnimMontageArray* montageArray = combatMontageMap.Find(type);

	//if (montageArray == nullptr)
		return EFistWeaponSlotFlag::None;

	//return StaticCast<EFistWeaponSlotFlag>(montageArray->hitBoxSlots[0]);
}

const TArray<UAnimMontage*>* UFistCombatAnimationData::GetMontageArray(const ECharacterCombatMontageType type) const
{
	const FFistAnimMontageArray* montageArray = combatMontageMap.Find(type);

	if (montageArray == nullptr)
		return nullptr;

	return &montageArray->montages;
}
