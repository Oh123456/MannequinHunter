// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/State.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FBaseMannequinHunterState : public FState
{
public:
	FBaseMannequinHunterState(uint8 id, EStateInitOption option = EStateInitOption::UseUpdate);
	virtual ~FBaseMannequinHunterState();
protected:
	uint8 OrderToStateID(uint16 order);
public:
	virtual void SetOwner(const TSharedPtr<FStateMachine>& owner) override;
private:
	UPROPERTY()
	TObjectPtr<class UStateSubsystem> stateSubsystem;
};
