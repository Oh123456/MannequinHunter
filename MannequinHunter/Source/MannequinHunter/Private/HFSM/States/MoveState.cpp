// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/MoveState.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/StateMachine.h"
#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Subsystem/StateSubsystem.h"

FMoveState::FMoveState() :
	FBaseMannequinHunterState(StaticCast<uint8>(EPlayerStateEnum::Move), DontUpdataAndConvertOrder)
{
	convertOrder->Add(StaticCast<uint16>(EStateOrder::Dodge));
	convertOrder->Add(StaticCast<uint16>(EStateOrder::Attack));
}

FMoveState::~FMoveState()
{
}

void FMoveState::Enter()
{
	APlayerCharacter* character = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	UAnimInstance* animInstance = character->GetMesh()->GetAnimInstance();
	animInstance->Montage_Stop(0.2f);

	character->GetCombatComponent()->ResetAttackCount();
}

uint8 FMoveState::Condition(uint16 order)
{
	uint8 newStateID = FState::Condition(order);

	if (convertOrder->Contains(order))
	{
		//newStateID = FStateManager::GetInstance()->GetStateID(order);
		newStateID = OrderToStateID(order);
	}

	//EStateOrder eOrder = StaticCast<EStateOrder>(order);

	//switch (eOrder)
	//{

	//case EStateOrder::Dodge:
	//	newStateID = StaticCast<uint8>(EPlayerStateEnum::Dodge);
	//	break;
	//case EStateOrder::Attack:
	//	newStateID = StaticCast<uint8>(EPlayerStateEnum::Attack);
	//	break;
	//}

	return newStateID;
}

uint8 FMoveState::UpdateCondition()
{
	APlayerCharacter* character = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	if (!character->IsMoveInput())
		return StaticCast<uint8>(EPlayerStateEnum::Idle);
	return GetStateID();
}
