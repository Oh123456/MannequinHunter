// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMannequinHunterState.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FInputWaitState : public FBaseMannequinHunterState
{
public:
	FInputWaitState();
	virtual ~FInputWaitState();

public:
	virtual void Enter() override;
	virtual uint8 Condition(uint16 order) override;

};
