// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/InputWaitState.h"
#include "Character/PlayerCommonEnums.h"
#include "Subsystem/StateSubsystem.h"
#include "HFSM/StateMachine.h"
#include "Controller/ActionPlayerController.h"
#include "GameFramework/Character.h"

FInputWaitState::FInputWaitState() : FBaseMannequinHunterState(StaticCast<uint8>(EPlayerStateEnum::InputWait), EStateInitOption::DontUpdataAndIgonereOrder)
{
	ignoreOrder->Add(StaticCast<uint16>(EStateOrder::Jump));
}

FInputWaitState::~FInputWaitState()
{
}

void FInputWaitState::Enter()
{
	AActionPlayerController* controller = Cast<AActionPlayerController>(ownerStateMachine->GetOwnerCharacter()->GetController());
	if (controller)
		controller->ExecuteInputBuffer();
}

uint8 FInputWaitState::Condition(uint16 order)
{
	uint16 newState = FState::Condition(order);
	if (ignoreOrder->Contains(order))
		return newState;

	//FStateManager* manager = FStateManager::GetInstance();
	newState = OrderToStateID(order);
	//newState = manager->GetStateID(order);

	return newState;
}
