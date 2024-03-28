// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/StatesMachines/DeathStateMachine.h"
#include "Character/PlayerCommonEnums.h"

#include "HFSM/States/DeathState.h"


FDeathStateMachine::FDeathStateMachine(UHFSMComponent* ownerCharacter) :
	FStateMachine(ownerCharacter, StaticCast<uint8>(EPlayerStateMachine::Death), StaticCast<uint8>(EPlayerStateEnum::Death))
{
}

FDeathStateMachine::~FDeathStateMachine()
{
}


void FDeathStateMachine::CreateStates()
{
	CreateState<FDeathState>(EPlayerStateEnum::Death);
}
