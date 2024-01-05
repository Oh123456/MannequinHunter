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

private:
	void ChangeCombat(uint16 order, OUT FStateMachineConditionResult& result);
protected:
	virtual void CreateStates() override;
};
