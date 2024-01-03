// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/HFSMComponent.h"
#include "HFSM/StateMachine.h"
#include "GameFramework/Character.h"
#include "DebugLog.h"

// Sets default values for this component's properties
UHFSMComponent::UHFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

UHFSMComponent::~UHFSMComponent()
{
	currentStateMachine = nullptr;
	stateMachines.Reset();
}

uint8 UHFSMComponent::GetCurrentStateMachineID()
{
	if (currentStateMachine == nullptr)
		return 0;
	return currentStateMachine->GetStateMachineID(); 
}

uint8 UHFSMComponent::GetCurrentStateID()
{
	return currentStateMachine->GetCurrentState();
}

void UHFSMComponent::ChangeState(uint8 changeStateID)
{
	TSharedPtr<FStateMachine>* findSateMachine = stateMachines.Find(changeStateID);
	if (findSateMachine)
	{
		(*findSateMachine)->ChangeState(changeStateID);
	}
}

void UHFSMComponent::ChangeStateMachine(uint8 changeStateID)
{
	TSharedPtr<FStateMachine>* findSateMachine = stateMachines.Find(changeStateID);
	if (findSateMachine)
	{
		if (currentStateMachine)
			currentStateMachine->Exit();

		currentStateMachine = *findSateMachine;
		currentStateMachine->Enter();
	}
}

void UHFSMComponent::CheckStateMachineCondition()
{
	
	uint8 stateID = currentStateMachine->Condition(stateMachineOrder);

	if (currentStateMachine->GetStateMachineID() != stateID)
	{
		if (currentStateMachine->EnterCondition())
			ChangeStateMachine(stateID);
	}

	// 초기화
	stateMachineOrder = 0;
}

void UHFSMComponent::SetStateOrder(uint16 order)
{
	stateMachineOrder = GetStateMachineOrder(order);
	if (stateMachineOrder != 0)
		CheckStateMachineCondition();
	// 현재 스테이트 머신에 스테이트 오더 전달
	currentStateMachine->SetStateOrder(GetStateOrder(order));
}

void UHFSMComponent::ChangeStateMachine()
{
	uint8 stateID = currentStateMachine->UpdateCondition(0);
	if (currentStateMachine->GetStateMachineID() != stateID)
		ChangeStateMachine(stateID);
}

// Called when the game starts
void UHFSMComponent::BeginPlay()
{
	Super::BeginPlay();
	SetStateMachine();
	SetConditions();

	ChangeStateMachine(defaultStateID);
}

TSharedPtr<FStateMachine>* UHFSMComponent::AddStateMachine(uint8 id, uint8 defaultSateID)
{

	TSharedPtr<FStateMachine>* find = stateMachines.Find(id);
	if (find == nullptr)
	{
		TSharedPtr<FStateMachine> stateMachine = MakeShared<FStateMachine>(FStateMachine(this, id, defaultSateID));
		find = &stateMachines.Add(id, stateMachine);
	}

	return find;
}

TSharedPtr<FStateMachine>* UHFSMComponent::FindStateMachine(uint8 id)
{
	return stateMachines.Find(id);
}

// Called every frame
void UHFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (currentStateMachine)
	{
		ChangeStateMachine();
		currentStateMachine->Update();
	}
}
uint16 UHFSMComponent::GetStateOrder(uint16 order)
{
	//uint16 value = stateOrder & HFSM_STATE_ORDER;
	//stateOrder = stateOrder & (HFSM_STATE_ORDER << 8);

	return order & HFSM_STATE_ORDER;
} 

uint16 UHFSMComponent::GetStateMachineOrder(uint16 order)
{
	return order & (HFSM_STATE_ORDER << 8);
}
