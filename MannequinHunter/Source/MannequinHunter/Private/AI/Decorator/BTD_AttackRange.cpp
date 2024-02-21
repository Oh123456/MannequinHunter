// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_AttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

bool UBTD_AttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();

	AActor* targetActor = Cast<AActor>(bbc->GetValueAsObject(GetSelectedBlackboardKey()));
	
	APawn* controlPawn = OwnerComp.GetAIOwner()->GetPawn();

	double disSquared = FVector::DistSquared(controlPawn->GetActorLocation(), controlPawn->GetActorLocation());

	return attackAbleRange >= disSquared;
}
