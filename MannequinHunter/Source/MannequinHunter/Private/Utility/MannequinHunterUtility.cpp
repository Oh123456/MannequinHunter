// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/MannequinHunterUtility.h"

const float FMannequinHunterUtility::PLAY_RATE_CONSTANT_NUMBER = 1.225f;
const float FMannequinHunterUtility::PLAY_RATE = 1.0f;

float FMannequinHunterUtility::GetPlayRate(int32 characterAttackSpeed)
{
	//https://www.desmos.com/calculator?lang=ko 그래프 사이트
	// 100 이상
	// y = 1.225^x + (1 - 1.225)
	// 100 미만
	// sin(x*0.5PI)
	float speed = characterAttackSpeed * 0.01f;
	if (characterAttackSpeed >= 100)
		return FMath::Pow(PLAY_RATE_CONSTANT_NUMBER, speed) + (1.0f - PLAY_RATE_CONSTANT_NUMBER);
	else
		return FMath::Sin(speed * 0.5 * UE_PI);
}
