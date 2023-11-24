// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/MoveState.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/StateMachine.h"
//#include "GameFramework/Character.h"
#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

FMoveState::FMoveState() :
FState(StaticCast<uint8>(EPlayerStateEnum::Move))
{
}

FMoveState::~FMoveState()
{
}

void FMoveState::Enter()
{
	ACharacter* character = ownerStateMachine->GetOwnerCharacter();
	UAnimInstance* animInstance = character->GetMesh()->GetAnimInstance();
	animInstance->Montage_Stop(0.2f);

}

uint8 FMoveState::Condition(uint16 order)
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

uint8 FMoveState::UpdateCondition()
{
	//ACharacter* character = ownerStateMachine->GetOwnerCharacter();
	//UCharacterMovementComponent* characterMovementComponent = character->GetCharacterMovement();
	//double speed = characterMovementComponent->Velocity.SizeSquared();
	//if (speed <= 0.0)
	//	return StaticCast<uint8>(EPlayerStateEnum::Idle);
	//return GetStateID();

	APlayerCharacter* character = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	//double speed = characterMovementComponent->Velocity.SizeSquared();
	//if (speed > 0.0)
	if (!character->IsMoveInput())
		return StaticCast<uint8>(EPlayerStateEnum::Idle);
	return GetStateID();
}
