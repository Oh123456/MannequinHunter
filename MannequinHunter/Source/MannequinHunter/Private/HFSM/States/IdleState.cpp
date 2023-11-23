// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/IdleState.h"
#include "HFSM/States/PlayerStateEnum.h"
#include "HFSM/StateMachine.h"
#include "Character/PlayerCommonEnums.h"
#include "DebugLog.h"

FIdleState::FIdleState() : 
	FState(StaticCast<uint8>(EPlayerStateEnum::Idle), 
		DONT_STATE_UPDATE)
{
}

FIdleState::~FIdleState()
{
}

uint8 FIdleState::Condition()
{
	uint8 newStateID = FState::Condition();
	
	EStateOrder order = ownerStateMachine->GetStateOrder<EStateOrder>();

	switch (order)
	{

	case EStateOrder::Dodge:
		newStateID = StaticCast<uint8>(EPlayerStateEnum::Dodge);
		break;
	case EStateOrder::Attack:
		newStateID = StaticCast<uint8>(EPlayerStateEnum::Attack);
		break;
	case EStateOrder::Jump:
		newStateID = StaticCast<uint8>(EPlayerStateEnum::Jump);
		break;
	}

	return newStateID;
}
