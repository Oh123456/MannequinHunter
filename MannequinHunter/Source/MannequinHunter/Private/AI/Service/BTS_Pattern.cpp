// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_Pattern.h"
#include "AI/AIPattern.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controller/BaseAIController.h"


UBTS_Pattern::UBTS_Pattern()
{
	bCreateNodeInstance = true;
}

void UBTS_Pattern::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AActor* targetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (patternClass && targetActor)
	{
		double distance = FVector::Distance(actorOwner->GetActorLocation(), targetActor->GetActorLocation());

		//ÀÌºÐ¹ý
		patternClass->

	}
}

void UBTS_Pattern::SetOwner(AActor* ActorOwner)
{
	actorOwner = ActorOwner;
	ABaseAIController* AIController = ActorOwner->GetInstigatorController<ABaseAIController>();

	if (AIController)
	{
		patternClass = AIController->GetAIPattern();
	}
}
