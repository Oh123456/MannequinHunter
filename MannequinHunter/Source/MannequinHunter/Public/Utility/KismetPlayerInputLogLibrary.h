// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KismetPlayerInputLogLibrary.generated.h"

enum class EPlayerInputType : uint8;
class ACharacter;
/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UKismetPlayerInputLogLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure)
	static const TArray<EPlayerInputType> GetPlayerInputs(ACharacter* character );
};
