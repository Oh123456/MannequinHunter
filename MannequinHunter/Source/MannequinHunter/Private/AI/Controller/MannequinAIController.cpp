// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/MannequinAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Utility/MannequinHunterTags.h"

void AMannequinAIController::BeginPlay()
{
	Super::BeginPlay();
	aiPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMannequinAIController::TargetPerceptionUpdated);
}

void AMannequinAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	Blackboard->SetValueAsVector("InitialLocation", InPawn->GetActorLocation());
}

void AMannequinAIController::TargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus)
{
	if (actor->ActorHasTag(MannequinHnterTags::PLAYER) )
	{
		
		if (stimulus.WasSuccessfullySensed())
		{
			Blackboard->SetValueAsBool("IsTarget", true);
			Blackboard->SetValueAsBool("IsLostTarget", false);
			Blackboard->SetValueAsObject("TargetActor", actor);
		}
		else
		{
			Blackboard->SetValueAsBool("IsTarget", false);
			Blackboard->SetValueAsBool("IsLostTarget", true);
			Blackboard->SetValueAsObject("TargetActor", nullptr);
		}
	}
}

