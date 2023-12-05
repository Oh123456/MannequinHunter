// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/State.h"

enum class ECharacterCombatontageType :uint8;

/**
 * 
 */
class MANNEQUINHUNTER_API FAttackState : public FState
{
public:
	FAttackState();
	~FAttackState();

protected:
	void CheckState();
private:

	ECharacterCombatontageType GetAnimSlot();
public:
	virtual void Enter();
	virtual uint8 Condition(uint16 order);

};
