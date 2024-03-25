// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/MannequinAIController.h"
#include "BossMannequinAIController.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API ABossMannequinAIController : public AMannequinAIController
{
	GENERATED_BODY()

protected:
	virtual void LostTarget(AActor* actor, FAIStimulus stimulus) override;
	
};
