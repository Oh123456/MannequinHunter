// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/StatesMachines/HitStateMachine.h"
#include "Character/PlayerCommonEnums.h"

#include "HFSM/States/HitState.h"

FHitStateMachine::FHitStateMachine(UHFSMComponent* ownerCharacter) :
 FStateMachine(ownerCharacter, StaticCast<uint8>(EPlayerStateMachine::Hit), StaticCast<uint8>(EPlayerStateEnum::Hit))
{
}

FHitStateMachine::~FHitStateMachine()
{
	
}

void FHitStateMachine::CreateStates()
{
	CreateState<FHitState>(EPlayerStateEnum::Hit);
}
