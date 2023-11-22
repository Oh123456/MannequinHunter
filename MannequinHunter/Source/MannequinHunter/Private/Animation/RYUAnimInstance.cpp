// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RYUAnimInstance.h"
#include "Character/RYU.h"
#include "HFSM/RYUHFSMComponent.h"

//bool URYUAnimInstance::IsCombat()
//{
//	ARYU* ryu = StaticCast<ARYU*>(ownerCharacter);
//
//	if (ryu == nullptr)
//		return false;
//
//	URYUHFSMComponent* RYUHFSMComponent = StaticCast<URYUHFSMComponent*>(ryu->GetHFSM());
//
//	return RYUHFSMComponent->IsCombat();
//}

ERYUWeaponType URYUAnimInstance::GetWeaponType()
{
	ARYU* ryu = StaticCast<ARYU*>(ownerCharacter);

	if (ryu == nullptr)
		return ERYUWeaponType::None;

	return ryu->GetWeaponType();
}

void URYUAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);

	weaponType = GetWeaponType();

	ryuStateMachineState = StaticCast<EPlayerStateMachine>(GetCurrentStateMachineID());
}
