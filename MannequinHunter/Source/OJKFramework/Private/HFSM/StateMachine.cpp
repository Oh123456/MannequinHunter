// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/StateMachine.h"
#include "HFSM/HFSMComponent.h"
#include "GameFramework/Character.h"
#include "HFSM/State.h"
#include "DebugLog.h"

FStateMachine::FStateMachine(UHFSMComponent* owner, uint8 stateMachineID, uint8 defaultStateID) :
	states(), stateMachineID(stateMachineID), currentState(nullptr)
	, defaultStateID(defaultStateID) , ownerCharacter(ownerCharacter)
{
	ownerCharacter = Cast<ACharacter>(owner->GetOwner());
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
		currentState->Enter();
}

void FStateMachine::Update()
{
	if (currentState)
	{
		int32 stateID = currentState->UpdateCondition();
		
		if (stateID != currentState->GetStateID())
		{
			ChangeState(stateID);
		}

		if (currentState->IsUpdate())
			currentState->Update();
	}
}

void FStateMachine::Exit()
{
	if (currentState)
	{
		currentState->Exit();
		currentState = nullptr;
	}
}

bool FStateMachine::EnterCondition()
{
	bool isSuccess = true;
	if (OnStateMachineEnterCondition.IsBound())
		OnStateMachineEnterCondition.Broadcast(OUT isSuccess);	
	return isSuccess;
}

uint8 FStateMachine::Condition(uint16 stateMachineOrder)
{	
	FStateMachineConditionResult result;
	OnStateMachineCondition.Broadcast(stateMachineOrder, OUT result);
	return result.stateID;
}

uint8 FStateMachine::UpdateCondition(uint16 stateMachineOrder)
{
	FStateMachineConditionResult result;
	OnUpdateStateMachineCondition.Broadcast(stateMachineOrder, OUT result);
	return result.stateID;
}

void FStateMachine::ChangeState(uint8 stateID)
{
	TSharedPtr<FState>* findState = states.Find(stateID);
	if (findState && (*findState)->EnterCondition())
	{
		currentState->Exit();
		currentState = *findState;
		if (currentState)
			currentState->Enter();

	}
}

void FStateMachine::SetStateOrder(uint16 order)
{
	 //this->stateOrder = order; 
	 if (currentState)
	 {
		 uint8 stateID = currentState->Condition(order);
		 
		 if (stateID != currentState->GetStateID())
			 ChangeState(stateID);
	 }
}

uint8 FStateMachine::GetCurrentState()
{
	if (currentState == nullptr)
		return 0;
	return currentState->GetStateID();
}
