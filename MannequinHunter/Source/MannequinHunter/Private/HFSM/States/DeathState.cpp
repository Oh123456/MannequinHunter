// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/DeathState.h"
#include "Character/PlayerCommonEnums.h"

FDeathState::FDeathState() : FBaseMannequinHunterState(StaticCast<uint8>(EPlayerStateEnum::Death), EStateInitOption::DontUpdate)
{
}

FDeathState::~FDeathState()
{
}
