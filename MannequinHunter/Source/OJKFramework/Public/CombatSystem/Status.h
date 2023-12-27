// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Status.generated.h"

struct FStatusDataTable;

USTRUCT(BlueprintType)
struct OJKFRAMEWORK_API FStatus 
{
	GENERATED_BODY()
public:
	FStatus() {}

	void SetStatus(const FStatusDataTable* dataAsset);

public:
	UPROPERTY(EditDefaultsOnly)
	int32 attack;
	UPROPERTY(EditDefaultsOnly)
	int32 health;
	UPROPERTY(EditDefaultsOnly)
	int32 defensive;
	UPROPERTY(EditDefaultsOnly )
	int32 maxHealth = 200;
};
