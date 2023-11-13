// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class OJKFRAMEWORK_API FState
{
public:
	FState(uint8 id);
	~FState();

	virtual void Enter() {}
	virtual void Update() {}
	virtual void Exit() {}
	virtual uint8 Condition(ACharacter* owner);

	inline uint8 GetStateID() const { return stateID; }

	template <typename T>
	inline T GetStateID() { return static_cast<T>(stateID); }

private:
	uint8 stateID;

};
