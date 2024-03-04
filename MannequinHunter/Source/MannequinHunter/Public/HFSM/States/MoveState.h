// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMannequinHunterState.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FMoveState : public FBaseMannequinHunterState
{
public:
	FMoveState();
	virtual ~FMoveState();


	virtual void Enter() override;
	virtual uint8 Condition(uint16 order) override;
	virtual uint8 UpdateCondition() override;
};
