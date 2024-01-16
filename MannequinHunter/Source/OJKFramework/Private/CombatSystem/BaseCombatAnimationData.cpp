// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/BaseCombatAnimationData.h"

const UAnimMontage* UBaseCombatAnimationData::GetMontage(const ECharacterCombatMontageType type, const int32 index) const
{
	const TArray<UAnimMontage*>* montageArray = GetMontageArray(type);
	UAnimMontage* montage = nullptr;
	if (montageArray)
	{
		if (montageArray->Num() > index)
			montage = (*montageArray)[index];
	}

	return montage;
}
