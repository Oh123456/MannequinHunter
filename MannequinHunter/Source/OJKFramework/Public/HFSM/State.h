// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//

class FStateMachine;

class OJKFRAMEWORK_API FState
{
protected:
	enum EStateInitOption : uint8
	{
		UseUpdate = 1,
		IgonereOrder = 1 << 1,
		ConvertOrder = 1 << 2,


		OnlyUpdate = UseUpdate,
		DontUpdatea = 0,

		UpdataAndIgonereOrder = UseUpdate | IgonereOrder,
		UpdataAndConvertOrder = UseUpdate | ConvertOrder,

		DontUpdataAndIgonereOrder = IgonereOrder,
		DontUpdataAndConvertOrder = ConvertOrder,

		IgonereOrderAndConvertOrder = IgonereOrder | ConvertOrder,

		ALL = OnlyUpdate | IgonereOrderAndConvertOrder,
	};
public:
	FState(uint8 id, EStateInitOption option = EStateInitOption::UseUpdate);
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
	virtual uint8 Condition(uint16 order);
	virtual uint8 UpdateCondition();

protected:
	TSharedPtr<FStateMachine> ownerStateMachine;
	TUniquePtr<TArray<uint16>> ignoreOrder;
	TUniquePtr<TArray<uint16>> convertOrder;
private:
	uint8 stateID;
	bool isUpdate;
};
