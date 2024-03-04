// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/HitState.h"
#include "Character/PlayerCommonEnums.h"

FHitState::FHitState() : 
	FBaseMannequinHunterState(StaticCast<uint8>(EPlayerStateEnum::Hit), EStateInitOption::DontUpdate)
{
}

FHitState::~FHitState()
{
}
