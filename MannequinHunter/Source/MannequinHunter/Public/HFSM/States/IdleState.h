// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/State.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FIdleState : public FState
{
public:
	FIdleState();
	virtual ~FIdleState();

public:
	virtual uint8 Condition(uint16 order) override;
	virtual uint8 UpdateCondition()  override;
};
