// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FState;
class UHFSMComponent;

class OJKFRAMEWORK_API FStateMachine
{
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FStateMachineCondition, OUT uint8&)
public:
	FStateMachine(ACharacter* ownerCharacter, uint8 stateMachineID , uint8 defaultStateID = 1);
	~FStateMachine();

	void Enter();
	void Update();
	void Exit();
	uint8 Condition();
	uint8 UpdateCondition();

	inline uint8 GetStateMachineID() const { return stateMachineID; }
	uint8 GetCurrentState();

	template<typename UClass>
	inline void AddUpdateStateCondition(UClass* uclass, void(UClass::* condition)(uint8&));

	template<typename UClass>
	inline void AddStateCondition(UClass* uclass, void(UClass::* condition)(uint8&));

private:
	uint8 stateMachineID;
	uint8 defaultStateID;
	TMap<uint8, TSharedPtr<FState>> states;
	TSharedPtr<FState> currentState;

	UPROPERTY()
	TObjectPtr<ACharacter> ownerCharacter;

	FStateMachineCondition OnUpdateStateMachineCondition;
	FStateMachineCondition OnStateMachineCondition;
};


template<typename UClass>
void FStateMachine::AddUpdateStateCondition(UClass* uclass,void(UClass::* condition)(uint8&))
{
	OnUpdateStateMachineCondition.AddUObject(uclass, condition);
}

template<typename UClass>
inline void FStateMachine::AddStateCondition(UClass* uclass, void(UClass::* condition)(uint8&))
{
	OnStateMachineCondition.AddUObject(uclass, condition);
}