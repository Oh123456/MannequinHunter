// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/JumpState.h"
#include "Character/PlayerCommonEnums.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "HFSM/StateMachine.h"
#include "Singleton/StateManager.h"

FJumpState::FJumpState() : FState(StaticCast<uint8>(EPlayerStateEnum::Jump) , DontUpdataAndConvertOrder)
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
		newState = FStateManager::GetInstance()->GetStateID(order);
	}

	//EStateOrder stateOrder = StaticCast<EStateOrder>(order);
	//
	//switch (stateOrder)
	//{
	//case EStateOrder::Attack:
	//	newState = StaticCast<uint8>(EPlayerStateEnum::Attack);
	//	break;
	//}
	return newState;
}

//uint8 FJumpState::UpdateCondition()
//{
//	bool isFalling = ownerStateMachine->GetOwnerCharacter()->GetMovementComponent()->IsFalling();
//	if (!isFalling)
//		return StaticCast<uint8>(EPlayerStateEnum::Idle);
//	return FState::UpdateCondition();
//}
