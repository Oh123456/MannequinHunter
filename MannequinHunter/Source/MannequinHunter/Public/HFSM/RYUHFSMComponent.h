// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/HFSMComponent.h"
#include "PlayerStateMachineEnum.h"
#include "States/PlayerStateEnum.h"
#include "RYUHFSMComponent.generated.h"

/**
 * 
 */


UCLASS(ClassGroup = (HFSM), meta = (BlueprintSpawnableComponent))
class MANNEQUINHUNTER_API URYUHFSMComponent : public UHFSMComponent
{
	GENERATED_BODY()
public:
	bool IsCombat() { return (GetCurrentStateMachineID() & StaticCast<uint8>(EPlayerStateMachine::Combat)); }

private:
	void ChangeCombat(uint16 stateOrder, OUT uint8& stateMachineID);

protected:
	virtual void BeginPlay() override;
	virtual void SetStateMachine() override;
	virtual void SetConditions() override;

private:
	UPROPERTY()
	TObjectPtr<class ARYU> ryuCharacter;

};

