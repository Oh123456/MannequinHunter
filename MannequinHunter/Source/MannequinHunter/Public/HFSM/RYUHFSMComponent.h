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
	Defulat = 0,
	Battle,
};

UCLASS()
class MANNEQUINHUNTER_API URYUHFSMComponent : public UHFSMComponent
{
	GENERATED_BODY()
	
};
