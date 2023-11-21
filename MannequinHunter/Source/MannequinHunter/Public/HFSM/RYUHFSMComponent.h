// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFSM/HFSMComponent.h"
#include "RYUHFSMComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ERYUStateMachine : uint8
{
	None = 0,
	Defulat,
	Falling,
	Hit,
	Combat = 1 << 7,
};

UCLASS()
class MANNEQUINHUNTER_API URYUHFSMComponent : public UHFSMComponent
{
	GENERATED_BODY()
public:
	bool IsCombat() { return (GetCurrentStateMachineID() & StaticCast<uint8>(ERYUStateMachine::Combat)); }

private:
	void ChangeCombat(OUT uint8& stateMachineID);

protected:
	virtual void BeginPlay() override;
	virtual void SetStateMachine() override;
	virtual void SetConditions() override;

private:
	UPROPERTY()
	TObjectPtr<class ARYU> ryuCharacter;
};
