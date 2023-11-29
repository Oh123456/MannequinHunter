// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Singleton.h"
#include "Character/PlayerCommonEnums.h"

//struct FStateData
//{
//	EPlayerStateEnum stateID = EPlayerStateEnum::None;
//	EPlayerStateMachine stateMachineID = EPlayerStateMachine::None;
//};

/**
 * 
 */
class MANNEQUINHUNTER_API FStateManager : public FSingleton<FStateManager>
{
public:
	FStateManager();
	virtual ~FStateManager();
public:
	uint8 GetStateID(EStateOrder order);
	template<typename T>
	uint8 GetStateID(T tOrder) { return GetStateID(StaticCast<EStateOrder>(tOrder)); }
private:
	TMap<EStateOrder, uint8> stateDataMap;

};
