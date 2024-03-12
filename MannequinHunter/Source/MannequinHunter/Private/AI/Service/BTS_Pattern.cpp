// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_Pattern.h"
#include "AI/AIPattern.h"
#include "Subsystem/AIManagerSubsystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controller/BaseAIController.h"


UBTS_Pattern::UBTS_Pattern()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

UBTS_Pattern::~UBTS_Pattern()
{
	patternData = nullptr;
	patternClass = nullptr;
	actorOwner = nullptr;
}

void UBTS_Pattern::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();
	AActor* targetActor = Cast<AActor>(bbc->GetValueAsObject(GetSelectedBlackboardKey()));
	if (patternClass && targetActor)
	{
		double distance = FVector::Distance(actorOwner->GetActorLocation(), targetActor->GetActorLocation());

		const TSharedPtr<FAIPatternTree>& pattern = patternClass->GetPattern();

		if (pattern)
		{
			const FPatternData* data = pattern->GetPatternData(StaticCast<int32>(distance));
			FName patternName = "None";
			if (data)
				patternName = data->GetPatternData().patternName;
			bbc->SetValueAsName(patternKeyName, patternName);
		}

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
