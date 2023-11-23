// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/JumpState.h"
#include "HFSM/States/PlayerStateEnum.h"
#include "Character/PlayerCommonEnums.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "HFSM/StateMachine.h"


FJumpState::FJumpState() : FState(StaticCast<uint8>(EPlayerStateEnum::Jump) , false)
{

}

FJumpState::~FJumpState()
{

}

uint8 FJumpState::Condition()
{
	uint8 newState = FState::Condition();
	bool isFalling = ownerStateMachine->GetOwnerCharacter()->GetMovementComponent()->IsFalling();
	if (!isFalling)
		return StaticCast<uint8>(EPlayerStateEnum::Idle);
	

	EStateOrder stateOrder = ownerStateMachine->GetStateOrder<EStateOrder>();

	switch (stateOrder)
	{
	case EStateOrder::Attack:
		newState = StaticCast<uint8>(EPlayerStateEnum::Attack);
		break;
	}
	return newState;
}
