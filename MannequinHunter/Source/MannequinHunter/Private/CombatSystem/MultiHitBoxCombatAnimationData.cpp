// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/MultiHitBoxCombatAnimationData.h"

UMultiHitBoxCombatAnimationData::UMultiHitBoxCombatAnimationData()
{
}

UMultiHitBoxCombatAnimationData::~UMultiHitBoxCombatAnimationData()
{
}

const TArray<uint8>* UMultiHitBoxCombatAnimationData::GetHitBoxSlot(const ECharacterCombatMontageType type)
{
	const FMultiHitBoxAnimMontageArray* montageArray = combatMontageMap.Find(type);

	if (montageArray == nullptr)
		return nullptr;

	return &montageArray->hitBoxSlots;
}

const TArray<UAnimMontage*>* UMultiHitBoxCombatAnimationData::GetMontageArray(const ECharacterCombatMontageType type) const
{
	const FMultiHitBoxAnimMontageArray* montageArray = combatMontageMap.Find(type);

	if (montageArray == nullptr)
		return nullptr;

	return &montageArray->montages;
}
