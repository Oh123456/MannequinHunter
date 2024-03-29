// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_BaseAnimation.h"
#include "Character/BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Subsystem/AIManagerSubsystem.h"
#include "Defines.h"

const FName SELFACTOR = TEXT("SelfActor");

void UBTT_BaseAnimation::PlayAnimation(ABaseEnemyCharacter* character, UBehaviorTreeComponent& OwnerComp, ECharacterCombatMontageType animSlot, float playRate)
{
	character->GetCombatComponent()->PlayAnimation(animSlot, playRate, [this, &OwnerComp]()
		{
			UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();
			bbc->SetValueAsEnum(this->enumKey.SelectedKeyName, StaticCast<uint8>(EEnemyState::Idle));
			bbc->SetValueAsName(this->GetSelectedBlackboardKey(), TEXT_NONE);
		}//, 
		//[this, &OwnerComp]()
		//{
		//	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();
		//	//bbc->SetValueAsName(this->GetSelectedBlackboardKey(), TEXT_NONE);
		//}
		);
}

bool UBTT_BaseAnimation::Condition(const UBlackboardComponent* bbc, const FPatternData* patternData)
{
	AActor* target = Cast<AActor>(bbc->GetValueAsObject(targetActorKey.SelectedKeyName));
	AActor* selfActor = Cast<AActor>(bbc->GetValueAsObject(SELFACTOR));
	float dis = FVector::DistSquared(selfActor->GetActorLocation(), target->GetTargetLocation());

	float conditionDis = patternData->GetPatternData().condition.distance;
	float powConditionDis = conditionDis * conditionDis;

	if (powConditionDis >= dis)
		return true;
	return false;
}
