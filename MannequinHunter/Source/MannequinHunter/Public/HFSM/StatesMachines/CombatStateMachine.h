// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/StateMachine.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FCombatStateMachine : public FStateMachine
{
public:
	FCombatStateMachine(UHFSMComponent* ownerCharacter);
	virtual ~FCombatStateMachine();

private:
	void ChangeCombat(uint16 order, OUT FStateMachineConditionResult& result);
protected:
	virtual void CreateStates() override;
	virtual void SetCondition() override;
};
