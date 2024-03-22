// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"

/**
 * 
 */

struct FStateMachineConditionResult
{
	uint8 stateID = 0;
	bool isChange = false;

	void SetStateID(uint8 id)
	{
		stateID = id;
		isChange = true;
	}

	void SetDefaultStateID(uint8 id)
	{
		stateID = id;
		isChange = false;
	}
};

//class FState;
class UHFSMComponent;

class OJKFRAMEWORK_API FStateMachine : public TSharedFromThis<FStateMachine>
{
public:
	//FUNC_DECLARE_MULTICAST_DELEGATE(FStateMachineCondition, uint8, uint16)
	DECLARE_MULTICAST_DELEGATE_TwoParams(FStateMachineCondition, uint16 ,OUT FStateMachineConditionResult&)
	DECLARE_MULTICAST_DELEGATE_OneParam(FStateMachineEnterCondition, OUT bool)
public:
	FStateMachine(UHFSMComponent* ownerCharacter, uint8 stateMachineID , uint8 defaultStateID = 1);
	virtual ~FStateMachine();

	void Init() { CreateStates(); SetCondition(); }

	void Enter();
	void Update();
	void Exit();
	bool EnterCondition();
	uint8 Condition(uint16 stateMachineOrder);
	uint8 UpdateCondition(uint16 stateMachineOrder);

	template<typename TState, typename TStateEnum>
	void CreateState(TStateEnum id);

	void ChangeState(uint8 stateID);

	void SetStateOrder(uint16 order);
	 
	template<typename T>
	T GetStateOrder() { return StaticCast<T>(GetStateOrder()); }

	UHFSMComponent* GetOwnerHFSM() { return ownerHFSM; }
	ACharacter* GetOwnerCharacter() { return ownerCharacter; }

	class UWorld* GetWorld() const;
	class UGameInstance* GetGameInstance() const;

	inline uint8 GetStateMachineID() const { return stateMachineID; }
	uint8 GetCurrentState();

	template<typename UClass>
	inline void AddUpdateStateCondition(UClass* uclass, void(UClass::* condition)(uint16, FStateMachineConditionResult&));

	template<typename UClass>
	inline void AddStateCondition(UClass* uclass, void(UClass::* condition)(uint16, FStateMachineConditionResult&));

	template<typename UClass>
	inline void AddStateEnterCondition(UClass* uclass, void(UClass::* condition)(bool));

	inline void AddState(uint8 stateid, TSharedPtr<FState>& newState) { states.Add(stateid, newState); }
	template<typename TStateEnum>
	inline void AddState(TStateEnum stateid, TSharedPtr<FState>& newState) { states.Add(StaticCast<uint8>(stateid), newState); }
protected:
	virtual void ChangeState(uint16 order, OUT FStateMachineConditionResult& result) {};
	virtual void CreateStates() {}
	virtual void SetCondition() {}
protected:
	uint8 stateMachineID;
	uint8 defaultStateID;

	TMap<uint8, TSharedPtr<FState>> states;
	TSharedPtr<FState> currentState;

	FStateMachineCondition OnUpdateStateMachineCondition;
	FStateMachineCondition OnStateMachineCondition;
	FStateMachineEnterCondition OnStateMachineEnterCondition;
private:
	UPROPERTY()
	TObjectPtr<ACharacter> ownerCharacter;
	UPROPERTY()
	TObjectPtr<UHFSMComponent> ownerHFSM;

};


template<typename UClass>
void FStateMachine::AddUpdateStateCondition(UClass* uclass, void(UClass::* condition)(uint16, FStateMachineConditionResult&))
{
	OnUpdateStateMachineCondition.AddUObject(uclass, condition);
}

template<typename UClass>
inline void FStateMachine::AddStateCondition(UClass* uclass, void(UClass::* condition)(uint16, FStateMachineConditionResult&))
{
	OnStateMachineCondition.AddUObject(uclass, condition);
}

template<typename UClass>
inline void FStateMachine::AddStateEnterCondition(UClass* uclass, void(UClass::* condition)(bool))
{
	OnStateMachineEnterCondition.AddUObject(uclass, condition);
}


template<typename TState, typename TStateEnum>
void FStateMachine::CreateState(TStateEnum id)
{
	TSharedPtr<FState> createState = MakeShared<TState>();

	createState->SetOwner(AsShared());
	AddState(id, createState);
}