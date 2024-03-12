// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_PatternAction.h"
#include "GameFramework/Character.h"
#include "AI/AIPattern.h"
#include "Subsystem/AIManagerSubsystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controller/MannequinAIController.h"

EBTNodeResult::Type UBTT_PatternAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();
	const FName& key = bbc->GetValueAsName(GetSelectedBlackboardKey());
	if (key == TEXT("None"))
		return EBTNodeResult::Type::Failed;

	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		ACharacter* character = Cast<ACharacter>(AIController->GetPawn());
		if (character)
		{
			const TSharedPtr<FAIPatternTree>& pattern = AIController->GetAIPattern()->GetPattern();
			const FPatternData* patternData = pattern->GetPatternData(key);
			if (patternData)
			{
				character->PlayAnimMontage(patternData->GetPatternData().montage);
				bbc->SetValueAsEnum(enumKey.SelectedKeyName, StaticCast<uint8>(EMannequinBlackBoardState::Attack));
				return EBTNodeResult::Type::Succeeded;
			}
		}

	}

	return EBTNodeResult::Type::Failed;
}
