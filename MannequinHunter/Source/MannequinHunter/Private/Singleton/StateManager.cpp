// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/StateManager.h"


FStateManager::FStateManager() : 
	stateDataMap()
{
	stateDataMap.Add(EStateOrder::Idle, StaticCast<uint8>(EPlayerStateEnum::Idle));
	stateDataMap.Add(EStateOrder::Attack, StaticCast<uint8>(EPlayerStateEnum::Attack));
	stateDataMap.Add(EStateOrder::Dodge, StaticCast<uint8>(EPlayerStateEnum::Dodge));
	stateDataMap.Add(EStateOrder::Jump, StaticCast<uint8>(EPlayerStateEnum::Jump));
	stateDataMap.Add(EStateOrder::InputWait, StaticCast<uint8>(EPlayerStateEnum::InputWait));



	stateDataMap.Add(EStateOrder::Falling, StaticCast<uint8>(EPlayerStateMachine::Falling));
	
}

FStateManager::~FStateManager()
{
	stateDataMap.Reset();
}

uint8 FStateManager::GetStateID(EStateOrder order)
{
	 uint8* find = stateDataMap.Find(order);
	 if (find == nullptr)
		 return 0;

	 return (*find);
}
