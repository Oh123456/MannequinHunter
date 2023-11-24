// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/RYUHFSMComponent.h"
#include "HFSM/StateMachine.h"
#include "Character/RYU.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/States/IdleState.h"
#include "HFSM/States/DodgeState.h"
#include "HFSM/States/JumpState.h"
#include "HFSM/States/MoveState.h"
#include "DebugLog.h"

void URYUHFSMComponent::SetStateMachine()
{
	TSharedPtr<FStateMachine>* stateMachine = AddStateMachine(EPlayerStateMachine::Defulat);
	(*stateMachine)->CreateState<FIdleState>(EPlayerStateEnum::Idle);
	(*stateMachine)->CreateState<FMoveState>(EPlayerStateEnum::Move);
	(*stateMachine)->CreateState<FDodgeState>(EPlayerStateEnum::Dodge);

	stateMachine = AddStateMachine(EPlayerStateMachine::Combat);
	(*stateMachine)->CreateState<FIdleState>(EPlayerStateEnum::Idle);
	(*stateMachine)->CreateState<FMoveState>(EPlayerStateEnum::Move);
	(*stateMachine)->CreateState<FDodgeState>(EPlayerStateEnum::Dodge);

	stateMachine = AddStateMachine(EPlayerStateMachine::Falling, EPlayerStateEnum::Jump);
	(*stateMachine)->CreateState<FJumpState>(EPlayerStateEnum::Jump);
}

void URYUHFSMComponent::SetConditions()
{
	TSharedPtr<FStateMachine>* stateMachine = FindStateMachine(EPlayerStateMachine::Defulat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeCombat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeFalling);

	stateMachine = FindStateMachine(EPlayerStateMachine::Combat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeCombat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeFalling);


	stateMachine = FindStateMachine(EPlayerStateMachine::Falling);
	(*stateMachine)->AddUpdateStateCondition(this, &URYUHFSMComponent::ChangeFallingEnd);
}


void URYUHFSMComponent::ChangeCombat(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(GetCurrentStateMachineID());
	
	if (order == StaticCast<uint16>(EStateOrder::ToggleCombat))
	{
		if (IsCombat())
			result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Defulat));
		else
			result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Combat));
	}

}

void URYUHFSMComponent::ChangeFalling(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(GetCurrentStateMachineID());

	uint16 fallingStateOrderID = StaticCast<uint16>(EStateOrder::Falling);
	
	if (order == fallingStateOrderID)
	{
		EPlayerStateMachine eStateMachine = StaticCast<EPlayerStateMachine>(result.stateID);
		if (eStateMachine == EPlayerStateMachine::Combat ||
			eStateMachine == EPlayerStateMachine::Defulat)
		{
			result.SetStateID(StaticCast<uint16>(EPlayerStateMachine::Falling));
		}
	}
}

void URYUHFSMComponent::ChangeFallingEnd(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(GetCurrentStateMachineID());

	if (!ryuCharacter->GetMovementComponent()->IsFalling())
	{
		if (IsCombat())
			result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Combat));
		else
			result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Defulat));
	}
}

void URYUHFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	ryuCharacter = static_cast<ARYU*>(GetOwner());
}
