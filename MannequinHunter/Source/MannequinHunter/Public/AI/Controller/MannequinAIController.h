// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/BaseAIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MannequinAIController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMannequinBlackBoardChase : uint8
{
	None = 0,
	LineofSight,
	Lost,
};

UCLASS()
class MANNEQUINHUNTER_API AMannequinAIController : public ABaseAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
private:
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus);
};
