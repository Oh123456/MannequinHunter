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
	TSharedPtr<FStateMachine>* AddStateMachine(uint8 id, uint8 defaultSateID = 0);

	template<typename T>
	TSharedPtr<FStateMachine>* AddStateMachine(T id, uint8 defaultSateID = 0);

	TSharedPtr<FStateMachine>* FindStateMachine(uint8 id);

	template<typename T>
	TSharedPtr<FStateMachine>* FindStateMachine(T id);

	template<typename T>
	T GetStateOrder() { return StaticCast<T>(GetStateOrder()); }

	template<typename T>
	T GetStateMachineOrder() { return StaticCast<T>(GetStateOrder()); }
private:	
	void ChangeStateMachine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void SetStateMachine() {};
	virtual void SetConditions() {};


	virtual uint16 GetStateOrder();
	virtual uint16 GetStateMachineOrder();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	uint16 stateOrder;
	uint16 stateMachineOrder;
	TMap<uint8, TSharedPtr<FStateMachine>> stateMachines;
	TSharedPtr<FStateMachine> currentStateMachine;

protected:
	UPROPERTY(EditAnywhere)
	uint8 defaultStateID = 1;
	
};


template<typename T>
TSharedPtr<FStateMachine>* UHFSMComponent::AddStateMachine(T id, uint8 defaultSateID)
{
  	return AddStateMachine(static_cast<uint8>(id), defaultSateID);
}


template<typename T>
TSharedPtr<FStateMachine>* UHFSMComponent::FindStateMachine(T id)
{
	return FindStateMachine(static_cast<uint8>(id));
}