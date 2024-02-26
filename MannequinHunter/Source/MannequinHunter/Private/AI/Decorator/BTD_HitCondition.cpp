// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_HitCondition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/BaseEnemyCharacter.h"

bool UBTD_HitCondition::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ABaseEnemyCharacter* enemyCharacter = Cast<ABaseEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemyCharacter == nullptr)
		return false;

	return enemyCharacter->IsState(EEnemyState::Hit);
}
