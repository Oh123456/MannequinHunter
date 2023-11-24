// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KismetHFSMLibrary.generated.h"


class UHFSMComponent;
class APlayerCharacter;

/**
 * 
 */
UCLASS(meta = (BlueprintThreadSafe, ScriptName = "HFSMLibrary"))
class OJKFRAMEWORK_API UKismetHFSMLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

	UFUNCTION(BlueprintPure)
	static uint8 GetCurrentStateID(UHFSMComponent* hfsm);

	UFUNCTION(BlueprintPure, DisplayName = "GetCurrentStateID From PlayerCharacter")
	static uint8 GetCurrentStateIDFromPlayerCharacter(APlayerCharacter* player);

	UFUNCTION(BlueprintPure)
	static uint8 GetCurrentStateMachineID(UHFSMComponent* hfsm);

	UFUNCTION(BlueprintPure, DisplayName = "GetCurrentStateMachineID From PlayerCharacter")
	static uint8 GetCurrentStateMachineIDFromPlayerCharacter(APlayerCharacter* player);
};
