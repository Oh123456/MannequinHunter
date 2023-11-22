// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/RYUHFSMComponent.h"
#include "HFSM/StateMachine.h"
#include "Character/RYU.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/States/IdleState.h"
#include "HFSM/States/DodgeState.h"

void URYUHFSMComponent::SetStateMachine()
{
	TSharedPtr<FStateMachine>* stateMachine = AddStateMachine(EPlayerStateMachine::Defulat);
	TSharedPtr<FState> createState = MakeShared<FIdleState>();
	(*stateMachine)->AddState(EPlayerStateEnum::Idle, createState);

	createState = MakeShared<FDodgeState>();
	(*stateMachine)->AddState(EPlayerStateEnum::Dodge, createState);


	AddStateMachine(EPlayerStateMachine::Combat);
}

void URYUHFSMComponent::SetConditions()
{
	TSharedPtr<FStateMachine>* stateMachine = FindStateMachine(EPlayerStateMachine::Defulat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeCombat);

	stateMachine = FindStateMachine(EPlayerStateMachine::Combat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeCombat);
}


void URYUHFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	ryuCharacter = static_cast<ARYU*>(GetOwner());
}

void URYUHFSMComponent::ChangeCombat(OUT uint8& stateMachineID)
{
	if (IsCombat())
		stateMachineID = StaticCast<uint8>(EPlayerStateMachine::Defulat);
	else
		stateMachineID = StaticCast<uint8>(EPlayerStateMachine::Combat);
}
