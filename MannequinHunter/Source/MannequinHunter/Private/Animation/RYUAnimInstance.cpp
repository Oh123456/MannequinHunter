// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RYUAnimInstance.h"
#include "Character/RYU.h"
#include "HFSM/RYUHFSMComponent.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"

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

EWeaponType URYUAnimInstance::GetWeaponType()
{
	ARYU* ryu = StaticCast<ARYU*>(ownerCharacter);

	if (ryu == nullptr)
		return EWeaponType::None;

	return StaticCast<UMannequinHunterCombatComponent*>(ryu->GetCombatComponent())->GetWeaponType();
}



void URYUAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void URYUAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);

	weaponType = GetWeaponType();

	ryuStateMachineState = StaticCast<EPlayerStateMachine>(GetCurrentStateMachineID());
}



void URYUAnimInstance::Death(const FDeathInfo& deathInfo)
{

	Super::Death(deathInfo);

	int8& max = weaponTypeDeathCounts[weaponType];

	deathAnimIndex = FMath::RandRange(0, max - 1);
}