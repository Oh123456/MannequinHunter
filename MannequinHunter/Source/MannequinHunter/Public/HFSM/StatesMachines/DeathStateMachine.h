// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/StateMachine.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FDeathStateMachine : public FStateMachine
{
public:
	FDeathStateMachine(UHFSMComponent* ownerCharacter);
	~FDeathStateMachine();

protected:
	virtual void CreateStates() override;
};
