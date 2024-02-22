// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/MannequinAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Utility/MannequinHunterTags.h"


const FName AMannequinAIController::CHASE_ENUM_KEY = TEXT("ChaseEnum");
const FName AMannequinAIController::TARGET_ACTOR_KEY = TEXT("TargetActor");

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
			Blackboard->SetValueAsEnum(CHASE_ENUM_KEY, static_cast<uint8>(EMannequinBlackBoardChase::LineofSight));
			Blackboard->SetValueAsObject(TARGET_ACTOR_KEY, actor);
		}
		else
		{
			Blackboard->SetValueAsEnum(CHASE_ENUM_KEY, static_cast<uint8>(EMannequinBlackBoardChase::Lost));
			Blackboard->SetValueAsObject(TARGET_ACTOR_KEY, nullptr);
		}
	}
}

