// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/MannequinAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Utility/MannequinHunterTags.h"
#include "Character/BaseEnemyCharacter.h"


void AMannequinAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	Blackboard->SetValueAsVector(INITIAL_LOCATION, InPawn->GetActorLocation());
	Blackboard->SetValueAsEnum(STATE_ENUM, StaticCast<uint8>(EEnemyState::Idle));
}

void AMannequinAIController::LookTarget(AActor* actor, FAIStimulus stimulus)
{
	Blackboard->SetValueAsEnum(CHASE_ENUM_KEY, static_cast<uint8>(EMannequinBlackBoardChase::LineofSight));
	Blackboard->SetValueAsObject(TARGET_ACTOR_KEY, actor);
}

void AMannequinAIController::LostTarget(AActor* actor, FAIStimulus stimulus)
{
	Blackboard->SetValueAsEnum(CHASE_ENUM_KEY, static_cast<uint8>(EMannequinBlackBoardChase::Lost));
	Blackboard->SetValueAsObject(TARGET_ACTOR_KEY, nullptr);
}

