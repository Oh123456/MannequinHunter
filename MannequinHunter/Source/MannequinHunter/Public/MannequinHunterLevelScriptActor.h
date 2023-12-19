// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MannequinHunterLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API AMannequinHunterLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
