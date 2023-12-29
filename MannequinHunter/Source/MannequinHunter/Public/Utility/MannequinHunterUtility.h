// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MANNEQUINHUNTER_API FMannequinHunterUtility
{
private:
	const static int32 DEFAULT_ATTACK_SPEED = 100;
	const static float PLAY_RATE_CONSTANT_NUMBER;
	const static float PLAY_RATE;

	FMannequinHunterUtility() = delete;
	FMannequinHunterUtility(const FMannequinHunterUtility& data) = delete;

public:
	static float GetPlayRate(int32 characterAttackSpeed);
};
