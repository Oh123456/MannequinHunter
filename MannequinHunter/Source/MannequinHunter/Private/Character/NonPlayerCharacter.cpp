// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NonPlayerCharacter.h"
#include "AI/Controller/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void ANonPlayerCharacter::SetBlackBoardState(uint8 state)
{
	UBlackboardComponent* bbc = GetController<AAIController>()->GetBlackboardComponent();
	bbc->SetValueAsEnum(ABaseAIController::STATE_ENUM, state);
}
