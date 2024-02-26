// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_SetState.h"
#include "Character/BaseEnemyCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_SetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseEnemyCharacter* character = Cast<ABaseEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;

	character->SetState(state);

	return EBTNodeResult::Succeeded;
}
