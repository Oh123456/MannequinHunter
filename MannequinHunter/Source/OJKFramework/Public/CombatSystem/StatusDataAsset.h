// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StatusDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class OJKFRAMEWORK_API UStatusDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	int32 attack;
	UPROPERTY(EditDefaultsOnly)
	int32 defensive;
	UPROPERTY(EditDefaultsOnly)
	int32 maxHealth = 200;
};
