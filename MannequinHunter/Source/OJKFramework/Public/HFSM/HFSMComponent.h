// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HFSMComponent.generated.h"

class FStateMachine;

#define HFSM_STATE_ORDER UINT8_MAX

UCLASS(ClassGroup=(HFSM), meta=(BlueprintSpawnableComponent) )
class OJKFRAMEWORK_API UHFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHFSMComponent();
	virtual ~UHFSMComponent();

	uint8 GetCurrentStateMachineID();
	uint8 GetCurrentStateID();

	//Forced Conversion State
	void ChangeState(uint8 changeStateID);

	//Forced Conversion StateMachine
	void ChangeStateMachine(uint8 changeStateID);

	// Current StateMachine Condition
	void CheckStateMachineCondition();

	void SetStateOrder(uint16 order);

	template<typename T>
	void SetStateOrder(T order) { SetStateOrder(StaticCast<uint16>(order)); }
protected:

	template<typename TStateMachine, typename T>
	TSharedPtr<FStateMachine>* AddStateMachine(T id);

	TSharedPtr<FStateMachine>* FindStateMachine(uint8 id);

	template<typename T>
	TSharedPtr<FStateMachine>* FindStateMachine(T id);

	template<typename T>
	T GetStateOrder(uint16 order) { return StaticCast<T>(GetStateOrder(uint16 order)); }

	template<typename T>
	T GetStateMachineOrder(uint16 order) { return StaticCast<T>(GetStateOrder(uint16 order)); }
private:	
	void ChangeStateMachine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void SetStateMachine() {};
	virtual void SetConditions() {};


	virtual uint16 GetStateOrder(uint16 order);
	virtual uint16 GetStateMachineOrder(uint16 order);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	uint16 stateMachineOrder;
	TMap<uint8, TSharedPtr<FStateMachine>> stateMachines;
	TSharedPtr<FStateMachine> currentStateMachine;

protected:
	UPROPERTY(EditAnywhere)
	uint8 defaultStateID = 1;
	
};

template<typename T>
TSharedPtr<FStateMachine>* UHFSMComponent::FindStateMachine(T id)
{
	return FindStateMachine(static_cast<uint8>(id));
}

template<typename TStateMachine, typename T>
TSharedPtr<FStateMachine>* UHFSMComponent::AddStateMachine(T tId)
{
	uint8 id = StaticCast<uint8>(tId);

	TSharedPtr<FStateMachine>* find = stateMachines.Find(id);
	if (find == nullptr)
	{
		TSharedPtr<FStateMachine> stateMachine = MakeShared<TStateMachine>(this);
		find = &stateMachines.Add(id, stateMachine);
		(*find)->Init();
	}

	return find;
}