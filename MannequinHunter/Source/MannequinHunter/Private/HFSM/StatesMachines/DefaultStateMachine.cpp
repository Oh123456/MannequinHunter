// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/StatesMachines/DefaultStateMachine.h"
#include "Character/PlayerCommonEnums.h"

#include "HFSM/States/IdleState.h"
#include "HFSM/States/MoveState.h"
#include "HFSM/States/DodgeState.h"

FDefaultStateMachine::FDefaultStateMachine(UHFSMComponent* ownerCharacter) :
	FStateMachine(ownerCharacter, StaticCast<uint8>(EPlayerStateMachine::Default), StaticCast<uint8>(EPlayerStateEnum::Idle))
{
	OnStateMachineCondition.AddRaw(this, &FDefaultStateMachine::ChangeCombat);
}

FDefaultStateMachine::~FDefaultStateMachine()
{
}

void FDefaultStateMachine::ChangeCombat(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(stateMachineID);

	if (order == StaticCast<uint16>(EStateOrder::ToggleCombat))
	{
		result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Combat));
	}

}

void FDefaultStateMachine::CreateStates()
{
	CreateState<FIdleState>(EPlayerStateEnum::Idle);
	CreateState<FMoveState>(EPlayerStateEnum::Move);
	CreateState<FDodgeState>(EPlayerStateEnum::Dodge);
}
