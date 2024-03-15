// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_SetStateIdle.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/BaseEnemyCharacter.h"

EBTNodeResult::Type UBTT_SetStateIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();

	bbc->SetValueAsEnum(GetSelectedBlackboardKey(), StaticCast<uint8>(EEnemyState::Idle));

	return EBTNodeResult::Type::Succeeded;
}
