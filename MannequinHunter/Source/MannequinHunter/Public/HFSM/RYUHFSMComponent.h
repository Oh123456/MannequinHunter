// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/HFSMComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "RYUHFSMComponent.generated.h"

/**
 * 
 */

struct FStateMachineConditionResult;

UCLASS(ClassGroup = (HFSM), meta = (BlueprintSpawnableComponent))
class MANNEQUINHUNTER_API URYUHFSMComponent : public UHFSMComponent
{
	GENERATED_BODY()
public:
	bool IsCombat() { return (GetCurrentStateMachineID() & StaticCast<uint8>(EPlayerStateMachine::Combat)); }

private:
	void ChangeCombat(uint16 order, OUT FStateMachineConditionResult& result);
	void ChangeFalling(uint16 order, OUT FStateMachineConditionResult& result);
	void ChangeFallingEnd(uint16 order, OUT FStateMachineConditionResult& result);
protected:
	virtual void BeginPlay() override;
	virtual void SetStateMachine() override;
	virtual void SetConditions() override;

private:
	UPROPERTY()
	TObjectPtr<class ARYU> ryuCharacter;

};

