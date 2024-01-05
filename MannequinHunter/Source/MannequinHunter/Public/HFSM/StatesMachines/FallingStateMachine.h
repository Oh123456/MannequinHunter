// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/StateMachine.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FFallingStateMachine : public FStateMachine
{
public:
	FFallingStateMachine(UHFSMComponent* ownerCharacter);
	~FFallingStateMachine();

protected:
	virtual void CreateStates() override;
};
