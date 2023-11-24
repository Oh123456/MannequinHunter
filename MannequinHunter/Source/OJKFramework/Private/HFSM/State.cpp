// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/State.h"

FState::FState(uint8 id, bool isUpdate) :
	stateID(id) , isUpdate(isUpdate)
{
}

FState::~FState()
{

}

uint8 FState::Condition(uint16 order)
{
	return stateID;
}

uint8 FState::UpdateCondition()
{
	return stateID;
}
