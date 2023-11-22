// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/StateMachine.h"
#include "HFSM/HFSMComponent.h"
#include "GameFramework/Character.h"
#include "HFSM/State.h"

FStateMachine::FStateMachine(ACharacter* ownerCharacter, uint8 stateMachineID, uint8 defaultStateID) :
	states(), stateMachineID(stateMachineID), currentState(nullptr)
	, defaultStateID(defaultStateID) , ownerCharacter(ownerCharacter)
{

}

FStateMachine::~FStateMachine()
{
	currentState = nullptr;
	ownerCharacter = nullptr;
	states.Reset();
}

void FStateMachine::Enter()
{
	if (states.IsEmpty())
		return;
	currentState = *states.Find(defaultStateID);
	if (currentState)
		currentState->Enter(ownerCharacter);
}

void FStateMachine::Update()
{
	if (currentState)
	{
		int32 stateID = currentState->Condition(ownerCharacter);
		
		if (stateID != currentState->GetStateID())
		{
			ChangeState(stateID);
		}

		if (currentState->IsUpdate())
			currentState->Update(ownerCharacter);
	}
}

void FStateMachine::Exit()
{
	if (currentState)
	{
		currentState->Exit(ownerCharacter);
		currentState = nullptr;
	}
}

uint8 FStateMachine::Condition()
{
	uint8 stateID = -1;

	OnStateMachineCondition.Broadcast(OUT stateID);

	return stateID;
	
}

uint8 FStateMachine::UpdateCondition()
{
	uint8 stateID = -1;
	OnUpdateStateMachineCondition.Broadcast(OUT stateID);

	return stateID;
}

void FStateMachine::ChangeState(uint8 stateID)
{
	TSharedPtr<FState>* findState = states.Find(stateID);
	if (findState)
	{
		currentState->Exit(ownerCharacter);
		currentState = *findState;
		if (currentState)
			currentState->Enter(ownerCharacter);
	}
}

uint8 FStateMachine::GetCurrentState()
{
	if (currentState == nullptr)
		return 0;
	return currentState->GetStateID();
}
