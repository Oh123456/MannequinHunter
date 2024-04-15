// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/JumpState.h"
#include "Character/PlayerCommonEnums.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "HFSM/StateMachine.h"
#include "Subsystem/StateSubsystem.h"

FJumpState::FJumpState() : FBaseMannequinHunterState(StaticCast<uint8>(EPlayerStateEnum::Jump) , DontUpdataAndConvertOrder)
{
	convertOrder->Add(StaticCast<uint16>(EStateOrder::Attack));
}

FJumpState::~FJumpState()
{

}

uint8 FJumpState::Condition(uint16 order)
{
	uint8 newState = FState::Condition(order);	

	if (convertOrder->Contains(order))
	{
		newState = OrderToStateID(order);
	}

	return newState;
}

