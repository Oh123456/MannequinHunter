// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

#define DONT_STATE_UPDATE false
//

class FStateMachine;

class OJKFRAMEWORK_API FState
{
public:
	FState(uint8 id, bool isUpdate = true);
	virtual ~FState();

	inline uint8 GetStateID() const { return stateID; }
	inline bool IsUpdate() const { return isUpdate; }
	template <typename T>
	inline T GetStateID() { return static_cast<T>(stateID); }

	void SetOwner(const TSharedPtr<FStateMachine>& owner) { ownerStateMachine = owner; };
public:
	virtual void Enter() {}
	virtual void Update() {}
	virtual void Exit() {}
	virtual uint8 Condition();

protected:
	TSharedPtr<FStateMachine> ownerStateMachine;
private:
	uint8 stateID;
	bool isUpdate;
};
