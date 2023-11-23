// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/RYUHFSMComponent.h"
#include "HFSM/StateMachine.h"
#include "Character/RYU.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/States/IdleState.h"
#include "HFSM/States/DodgeState.h"
#include "HFSM/States/JumpState.h"

void URYUHFSMComponent::SetStateMachine()
{
	TSharedPtr<FStateMachine>* stateMachine = AddStateMachine(EPlayerStateMachine::Defulat);
	(*stateMachine)->CreateState<FIdleState>(EPlayerStateEnum::Idle);
	(*stateMachine)->CreateState<FDodgeState>(EPlayerStateEnum::Dodge);
	(*stateMachine)->CreateState<FJumpState>(EPlayerStateEnum::Jump);

	AddStateMachine(EPlayerStateMachine::Combat);
}

void URYUHFSMComponent::SetConditions()
{
	TSharedPtr<FStateMachine>* stateMachine = FindStateMachine(EPlayerStateMachine::Defulat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeCombat);

	stateMachine = FindStateMachine(EPlayerStateMachine::Combat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeCombat);
}


void URYUHFSMComponent::ChangeCombat(uint16 order, OUT uint8& stateMachineID)
{
	stateMachineID = GetCurrentStateMachineID();

	if (order == StaticCast<uint16>(EStateOrder::ToggleCombat))
	{
		if (IsCombat())
			stateMachineID = StaticCast<uint8>(EPlayerStateMachine::Defulat);
		else
			stateMachineID = StaticCast<uint8>(EPlayerStateMachine::Combat);
	}

}

void URYUHFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	ryuCharacter = static_cast<ARYU*>(GetOwner());
}
