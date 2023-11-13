// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/State.h"

FState::FState(uint8 id) :
	stateID(id)
{
}

FState::~FState()
{

}

uint8 FState::Condition(ACharacter* owner)
{
	return stateID;
}
