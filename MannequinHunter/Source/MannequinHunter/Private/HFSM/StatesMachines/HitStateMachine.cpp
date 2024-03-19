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

void FHitStateMachine::ChangeState(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(stateMachineID);

	if (order == StaticCast<uint16>(EStateOrder::Combat))
		result.SetStateID(StaticCast<uint16>(EPlayerStateMachine::Combat));
}

void FHitStateMachine::CreateStates()
{
	CreateState<FHitState>(EPlayerStateEnum::Hit);
}

void FHitStateMachine::SetCondition()
{
	OnStateMachineCondition.AddRaw(this, &FHitStateMachine::ChangeState);
}
