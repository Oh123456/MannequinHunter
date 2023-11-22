// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

#define DONT_STATE_UPDATE false
//
//DECLARE_EVENT_OneParam(FState, FEnterEvnet, ACharacter*);
//DECLARE_EVENT_OneParam(FState, FUpdateEvnet, ACharacter*);
//DECLARE_EVENT_OneParam(FState, FExitEvnet, ACharacter*);

class OJKFRAMEWORK_API FState
{
public:
	FState(uint8 id, bool isUpdate = true);
	virtual ~FState();

	inline uint8 GetStateID() const { return stateID; }
	inline bool IsUpdate() const { return isUpdate; }
	template <typename T>
	inline T GetStateID() { return static_cast<T>(stateID); }

public:
	virtual void Enter(ACharacter* owner) {}
	virtual void Update(ACharacter* owner) {}
	virtual void Exit(ACharacter* owner) {}
	virtual uint8 Condition(ACharacter* owner);
	// º¸·ù
//public: 
//	FEnterEvnet OnEnter;
//	FUpdateEvnet OnUpdate;
//	FExitEvnet OnExit;
private:
	uint8 stateID;
	bool isUpdate;
};
