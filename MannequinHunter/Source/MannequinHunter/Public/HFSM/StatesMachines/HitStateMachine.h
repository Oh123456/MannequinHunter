// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/StateMachine.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FHitStateMachine : public FStateMachine
{
public:
	FHitStateMachine(UHFSMComponent* ownerCharacter);
	~FHitStateMachine();

protected:
	virtual void ChangeState(uint16 order, OUT FStateMachineConditionResult& result) override;
	virtual void CreateStates() override;
	virtual void SetCondition() override;
};
