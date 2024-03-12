// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/BaseAIController.h"
#include "AI/AIPattern.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
{
	aiPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

const UAIPattern* ABaseAIController::GetAIPattern() const
{
	 return AIPattern.GetDefaultObject(); 
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	if (AIPattern)
	{
		AIPattern.GetDefaultObject()->LoadTableData(GetWorld());
	}
	RunBehaviorTree(behaviorTree);
}
