// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_ChangeEnum.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controller/MannequinAIController.h"

EBTNodeResult::Type UBTT_ChangeEnum::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), changeValue);

	return EBTNodeResult::Succeeded;

}
