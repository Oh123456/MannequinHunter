// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/StatesMachines/FallingStateMachine.h"
#include "Character/PlayerCommonEnums.h"

#include "HFSM/States/JumpState.h"

FFallingStateMachine::FFallingStateMachine(UHFSMComponent* ownerCharacter) : 
	FStateMachine(ownerCharacter, StaticCast<uint8>(EPlayerStateMachine::Falling), StaticCast<uint8>(EPlayerStateEnum::Jump))
{
}

FFallingStateMachine::~FFallingStateMachine()
{
}


void FFallingStateMachine::CreateStates()
{
	CreateState<FJumpState>(EPlayerStateEnum::Jump);
}
