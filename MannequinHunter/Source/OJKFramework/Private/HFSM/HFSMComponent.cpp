// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/HFSMComponent.h"
#include "HFSM/StateMachine.h"
#include "GameFramework/Character.h"

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
		if (currentStateMachine)
			currentStateMachine->Exit();

		currentStateMachine = *findSateMachine;
		currentStateMachine->Enter();
	}
}


// Called when the game starts
void UHFSMComponent::BeginPlay()
{
	Super::BeginPlay();
	SetStateMachine();
	SetConditions();

	ChangeState(defaultStateID);
}

TSharedPtr<FStateMachine>* UHFSMComponent::AddStateMachine(uint8 id, uint8 defaultSateID)
{

	TSharedPtr<FStateMachine>* find = stateMachines.Find(id);
	if (find == nullptr)
	{
		TSharedPtr<FStateMachine> stateMachine = MakeShared<FStateMachine>(FStateMachine(Cast<ACharacter>(GetOwner()), id, defaultSateID));
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
		uint8 stateID = currentStateMachine->Condition();
		if (currentStateMachine->GetStateMachineID() != stateID)
			ChangeState(stateID);
		currentStateMachine->Update();
	}
}



