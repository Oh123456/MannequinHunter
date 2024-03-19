// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/StateMachine.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FDefaultStateMachine : public FStateMachine
{
public:
	FDefaultStateMachine(UHFSMComponent* ownerCharacter);
	virtual ~FDefaultStateMachine();

protected:
	virtual void ChangeState(uint16 order, OUT FStateMachineConditionResult& result) override;
	virtual void CreateStates() override;
	virtual void SetCondition() override;
};
