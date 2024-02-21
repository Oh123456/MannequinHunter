// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
protected:
	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<UAIPerceptionComponent> aiPerception;
private:
	UPROPERTY(EditAnywhere, Category = BehaviorTree, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> behaviorTree;
};
