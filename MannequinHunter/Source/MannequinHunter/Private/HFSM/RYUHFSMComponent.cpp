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
	//(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::CommonToCombatCondition);

	stateMachine = FindStateMachine(ERYUStateMachine::Combat);
	//(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::CommonToCombatCondition);
}


void URYUHFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	ryuCharacter = static_cast<ARYU*>(GetOwner());
}

void URYUHFSMComponent::ChangeCombat(bool isCombat)
{
}
