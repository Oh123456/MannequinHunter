// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/StatesMachines/CombatStateMachine.h"
#include "Character/PlayerCommonEnums.h"

#include "HFSM/States/IdleState.h"
#include "HFSM/States/MoveState.h"
#include "HFSM/States/DodgeState.h"
#include "HFSM/States/AttackState.h"
#include "HFSM/States/InputWaitState.h"

FCombatStateMachine::FCombatStateMachine(UHFSMComponent* ownerCharacter) :
	FStateMachine(ownerCharacter, StaticCast<uint8>(EPlayerStateMachine::Combat), StaticCast<uint8>(EPlayerStateEnum::Idle))
{
	
}

FCombatStateMachine::~FCombatStateMachine()
{
}

void FCombatStateMachine::ChangeState(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(stateMachineID);

	if (order == StaticCast<uint16>(EStateOrder::ToggleCombat))
		result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Default));
	else if (order == StaticCast<uint16>(EStateOrder::StatemMachineHit))
		result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Hit));

}


void FCombatStateMachine::CreateStates()
{
	CreateState<FIdleState>(EPlayerStateEnum::Idle);
	CreateState<FInputWaitState>(EPlayerStateEnum::InputWait);
	CreateState<FMoveState>(EPlayerStateEnum::Move);
	CreateState<FDodgeState>(EPlayerStateEnum::Dodge);
	CreateState<FAttackState>(EPlayerStateEnum::Attack);
}

void FCombatStateMachine::SetCondition()
{
	OnStateMachineCondition.AddRaw(this, &FCombatStateMachine::ChangeState);
}
