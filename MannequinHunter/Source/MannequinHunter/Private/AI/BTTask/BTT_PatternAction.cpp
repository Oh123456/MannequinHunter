// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_PatternAction.h"
#include "Character/BaseEnemyCharacter.h"
#include "AI/AIPattern.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Subsystem/AIManagerSubsystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controller/MannequinAIController.h"

EBTNodeResult::Type UBTT_PatternAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();
	const FName& key = bbc->GetValueAsName(GetSelectedBlackboardKey());
	if (key == TEXT_NONE)
		return EBTNodeResult::Type::Failed;

	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		ABaseEnemyCharacter* character = Cast<ABaseEnemyCharacter>(AIController->GetPawn());
		if (character)
		{
			const TSharedPtr<FAIPatternTree>& pattern = AIController->GetAIPattern()->GetPattern();
			const FPatternData* patternData = pattern->GetPatternData(key);
			if (patternData)
			{
				PlayAnimation(character, OwnerComp, patternData->GetPatternData().animSlot, 1.0f);
				bbc->SetValueAsEnum(enumKey.SelectedKeyName, StaticCast<uint8>(EEnemyState::Attack));
				return EBTNodeResult::Type::Succeeded;
			}
		}

	}

	return EBTNodeResult::Type::Failed;
}
