// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/RYUHFSMComponent.h"
#include "HFSM/StateMachine.h"
#include "Character/RYU.h"

void URYUHFSMComponent::SetStateMachine()
{
	AddStateMachine(ERYUStateMachine::Defulat);
	AddStateMachine(ERYUStateMachine::Combat);
}

void URYUHFSMComponent::SetConditions()
{
	TSharedPtr<FStateMachine>* stateMachine = FindStateMachine(ERYUStateMachine::Defulat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeCombat);

	stateMachine = FindStateMachine(ERYUStateMachine::Combat);
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
		stateMachineID = StaticCast<uint8>(ERYUStateMachine::Defulat);
	else
		stateMachineID = StaticCast<uint8>(ERYUStateMachine::Combat);
}
