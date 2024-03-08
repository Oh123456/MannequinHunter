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
}

void UBTS_Pattern::SetOwner(AActor* ActorOwner)
{
	ABaseAIController* AIController = ActorOwner->GetInstigatorController<ABaseAIController>();

	if (AIController)
	{
		const UAIPattern* AIPattern = AIController->GetAIPattern();
	}
}
