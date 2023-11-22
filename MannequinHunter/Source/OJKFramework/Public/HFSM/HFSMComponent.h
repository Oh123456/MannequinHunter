// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HFSMComponent.generated.h"

class FStateMachine;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

protected:
	TSharedPtr<FStateMachine>* AddStateMachine(uint8 id, uint8 defaultSateID = 0);

	template<typename T>
	TSharedPtr<FStateMachine>* AddStateMachine(T id, uint8 defaultSateID = 0);

	TSharedPtr<FStateMachine>* FindStateMachine(uint8 id);

	template<typename T>
	TSharedPtr<FStateMachine>* FindStateMachine(T id);

private:	
	void ChangeStateMachine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void SetStateMachine() {};
	virtual void SetConditions() {};

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere)
	uint8 defaultStateID = 1;

private:

	TMap<uint8, TSharedPtr<FStateMachine>> stateMachines;
	TSharedPtr<FStateMachine> currentStateMachine;

	
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