// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/State.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FDodgeState : public FState
{
public:
	FDodgeState();
	virtual ~FDodgeState();

public:
	virtual void Enter() override;
	virtual uint8 Condition(uint16 order) override;
	virtual uint8 UpdateCondition() override;


private:
	bool isDodgeEnd;
};
