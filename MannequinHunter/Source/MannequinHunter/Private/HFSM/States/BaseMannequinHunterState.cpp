// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/BaseMannequinHunterState.h"
#include "Subsystem/StateSubsystem.h"
#include "HFSM/StateMachine.h"


FBaseMannequinHunterState::FBaseMannequinHunterState(uint8 id, EStateInitOption option) :
	FState(id, option)
{
}

FBaseMannequinHunterState::~FBaseMannequinHunterState()
{
	stateSubsystem = nullptr;
}

uint8 FBaseMannequinHunterState::OrderToStateID(uint16 order)
{
	return stateSubsystem->GetStateID(order);
}

void FBaseMannequinHunterState::SetOwner(const TSharedPtr<FStateMachine>& owner)
{
	FState::SetOwner(owner);

	stateSubsystem = ownerStateMachine->GetGameInstance()->GetSubsystem<UStateSubsystem>();
}
