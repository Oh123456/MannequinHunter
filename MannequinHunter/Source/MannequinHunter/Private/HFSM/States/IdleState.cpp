// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/IdleState.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/StateMachine.h"
#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

FIdleState::FIdleState() : 
	FState(StaticCast<uint8>(EPlayerStateEnum::Idle))
{
}

FIdleState::~FIdleState()
{
}

uint8 FIdleState::Condition(uint16 order)
{
	uint8 newStateID = FState::Condition(order);
	
	EStateOrder eOrder = StaticCast<EStateOrder>(order);
	switch (eOrder)
	{

	case EStateOrder::Dodge:
		newStateID = StaticCast<uint8>(EPlayerStateEnum::Dodge);
		break;
	case EStateOrder::Attack:
		newStateID = StaticCast<uint8>(EPlayerStateEnum::Attack);
		break;
	}

	return newStateID;
}

uint8 FIdleState::UpdateCondition()
{
	APlayerCharacter* character = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	//double speed = characterMovementComponent->Velocity.SizeSquared();
	//if (speed > 0.0)
	if (character->IsMoveInput())
		return StaticCast<uint8>(EPlayerStateEnum::Move);
	return GetStateID();
}
