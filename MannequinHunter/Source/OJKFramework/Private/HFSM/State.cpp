// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/State.h"

FState::FState(uint8 id, EStateInitOption option) :
	stateID(id) , isUpdate(option & EStateInitOption::UseUpdate), ignoreOrder(nullptr), convertOrder(nullptr)
{
	if (option & EStateInitOption::IgonereOrder)
		ignoreOrder = MakeUnique<TArray<uint16>>();
	if (option & EStateInitOption::ConvertOrder)
		convertOrder = MakeUnique<TArray<uint16>>();
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
