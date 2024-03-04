// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMannequinHunterState.h"

enum class ECharacterCombatMontageType :uint8;

/**
 * 
 */
class MANNEQUINHUNTER_API FAttackState : public FBaseMannequinHunterState
{
public:
	FAttackState();
	virtual ~FAttackState();

protected:
	void CheckState();
private:

	ECharacterCombatMontageType GetAnimSlot();
public:
	virtual void Enter() override;
	virtual void Exit() override;
	virtual uint8 Condition(uint16 order) override;
	virtual bool EnterCondition() override;
private:
	ECharacterCombatMontageType attackMontageType;
};
