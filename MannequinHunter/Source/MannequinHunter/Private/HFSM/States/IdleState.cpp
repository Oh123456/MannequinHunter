// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/IdleState.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/StateMachine.h"
#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Singleton/StateManager.h"

FIdleState::FIdleState() : 
	FState(StaticCast<uint8>(EPlayerStateEnum::Idle), EStateInitOption::UpdataAndConvertOrder)
{
	convertOrder->Add(StaticCast<uint16>(EStateOrder::Dodge));
	convertOrder->Add(StaticCast<uint16>(EStateOrder::Attack));
}

FIdleState::~FIdleState()
{
}

uint8 FIdleState::Condition(uint16 order)
{
	uint8 newStateID = FState::Condition(order);
	
	if (convertOrder->Contains(order))
		newStateID = FStateManager::GetInstance()->GetStateID(order);

	/*EStateOrder eOrder = StaticCast<EStateOrder>(order);
	switch (eOrder)
	{

	case EStateOrder::Dodge:
		newStateID = StaticCast<uint8>(EPlayerStateEnum::Dodge);
		break;
	case EStateOrder::Attack:
		newStateID = StaticCast<uint8>(EPlayerStateEnum::Attack);
		break;
	}*/

	return newStateID;
}

uint8 FIdleState::UpdateCondition()
{
	APlayerCharacter* character = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	if (character->IsMoveInput())
		return StaticCast<uint8>(EPlayerStateEnum::Move);
	return GetStateID();
}
