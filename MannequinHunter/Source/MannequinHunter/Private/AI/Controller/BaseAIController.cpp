// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/BaseAIController.h"
#include "AI/AIPattern.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
{
	aiPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(behaviorTree);

	if (AIPattern)
	{
		AIPattern.GetDefaultObject()->LoadTableData();
		UBlackboardComponent* bbc = GetBlackboardComponent();

		bbc->SetValueAsClass(AIPatternKey, AIPattern);
	}
}
