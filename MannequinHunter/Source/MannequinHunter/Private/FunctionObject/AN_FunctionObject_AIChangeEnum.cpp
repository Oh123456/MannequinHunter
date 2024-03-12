// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionObject/AN_FunctionObject_AIChangeEnum.h"
#include "AI/Controller/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UAN_FunctionObject_AIChangeEnum::ChangeEnum(int64 value, USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	ABaseAIController* AIController = meshComp->GetOwner()->GetInstigatorController<ABaseAIController>();
	if (AIController)
	{
		UBlackboardComponent* bbc = AIController->GetBlackboardComponent();
		if (bbc)
		{
			bbc->SetValueAsEnum(blackBoardKeyName, value);
		}
	}
}
