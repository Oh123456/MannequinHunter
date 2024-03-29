// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_IsDeath.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_IsDeath::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();

	return bbc->GetValueAsBool(GetSelectedBlackboardKey());
}
