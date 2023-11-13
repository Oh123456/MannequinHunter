// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RYUAnimInstance.h"
#include "Character/RYU.h"

ERYUWeaponType URYUAnimInstance::GetWeaponType()
{
	ARYU* ryu = static_cast<ARYU*>(ownerCharacter);

	if (ryu == nullptr)
		return ERYUWeaponType::None;

	return ryu->GetWeaponType();
}

void URYUAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);

	weaponType = GetWeaponType();
}
