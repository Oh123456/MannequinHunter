// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/StatesMachines/DefaultStateMachine.h"
#include "Character/PlayerCommonEnums.h"

#include "HFSM/States/IdleState.h"
#include "HFSM/States/MoveState.h"
#include "HFSM/States/DodgeState.h"

FDefaultStateMachine::FDefaultStateMachine(UHFSMComponent* ownerCharacter) :
	FStateMachine(ownerCharacter, StaticCast<uint8>(EPlayerStateMachine::Default), StaticCast<uint8>(EPlayerStateEnum::Idle))
{
}

FDefaultStateMachine::~FDefaultStateMachine()
{
}

void FDefaultStateMachine::ChangeState(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(stateMachineID);

	if (order == StaticCast<uint16>(EStateOrder::ToggleCombat))
		result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Combat));
	else if (order == StaticCast<uint16>(EStateOrder::StatemMachineHit))
		result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Hit));

}

void FDefaultStateMachine::CreateStates()
{
	CreateState<FIdleState>(EPlayerStateEnum::Idle);
	CreateState<FMoveState>(EPlayerStateEnum::Move);
	CreateState<FDodgeState>(EPlayerStateEnum::Dodge);
}

void FDefaultStateMachine::SetCondition()
{
	OnStateMachineCondition.AddRaw(this, &FDefaultStateMachine::ChangeState);
}
