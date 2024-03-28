// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_BaseAnimation.h"
#include "Character/BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Defines.h"

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
