// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/IdleState.h"
#include "HFSM/States/PlayerStateEnum.h"
#include "Player/PlayerCharacter.h"

FIdleState::FIdleState() : 
	FState(StaticCast<uint8>(EPlayerStateEnum::Idle), 
		DONT_STATE_UPDATE)
{
}

FIdleState::~FIdleState()
{
}

uint8 FIdleState::Condition(ACharacter* owner)
{
	uint8 newstateID = FState::Condition(owner);
	
	APlayerCharacter* player = StaticCast<APlayerCharacter*>(owner);
	if (player)
	{
		using EStateOrder = APlayerCharacter::EStateOrder;

		EStateOrder order = player->GetStateOrder();

		if (order == EStateOrder::Dodge)
			newstateID = StaticCast<uint8>(EPlayerStateEnum::Dodge);
		else if(order == EStateOrder::Attack)
			newstateID = StaticCast<uint8>(EPlayerStateEnum::Attack);
		//switch (order)
		//{
		//case EStateOrder::Dodge:
		//	newstateID = StaticCast<uint8>(EPlayerStateEnum::Dodge);
		//case EStateOrder::Attack:
		//	newstateID = StaticCast<uint8>(EPlayerStateEnum::Attack);
		//	break;
		//}
		
	}

	return newstateID;
}
