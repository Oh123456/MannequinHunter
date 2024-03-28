// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_AdditionalAttack.h"
#include "Character/BaseEnemyCharacter.h"
#include "AI/AIPattern.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Subsystem/AIManagerSubsystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controller/MannequinAIController.h"
#include "Utility/MannequinHunterUtility.h"

EBTNodeResult::Type UBTT_AdditionalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();

	const FName& key = bbc->GetValueAsName(GetSelectedBlackboardKey());
	
	bbc->SetValueAsName(GetSelectedBlackboardKey(), TEXT_NONE);
	if (key == TEXT_NONE)
		return EBTNodeResult::Type::Failed;

	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (AIController == nullptr)
		return EBTNodeResult::Type::Failed;

	ABaseEnemyCharacter* character = Cast<ABaseEnemyCharacter>(AIController->GetPawn());

	if (character == nullptr)
		return EBTNodeResult::Type::Failed;

	const TSharedPtr<FAIPatternTree>& pattern = AIController->GetAIPattern()->GetPattern();
	const FPatternData* patternData = pattern->GetPatternData(key);

	if (patternData == nullptr)
		return EBTNodeResult::Type::Failed;

	const FName& name = patternData->GetPatternStateData().GetPattern();

	if (name == TEXT_NONE)
		return EBTNodeResult::Type::Failed;

	patternData = pattern->GetPatternData(name);

	if (patternData == nullptr)
		return EBTNodeResult::Type::Failed;

	float playRate = FMannequinHunterUtility::GetPlayRate(character->GetCombatComponent()->GetStatusData().GetStatusData()->attackSpeed);
	PlayAnimation(character, OwnerComp, patternData->GetPatternData().animSlot, playRate);

	bbc->SetValueAsName(GetSelectedBlackboardKey(), name);
	bbc->SetValueAsEnum(enumKey.SelectedKeyName, StaticCast<uint8>(EEnemyState::Attack));
	return EBTNodeResult::Type::Succeeded;

}