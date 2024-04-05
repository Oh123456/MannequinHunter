// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_BaseAnimation.h"
#include "Character/BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Subsystem/AIManagerSubsystem.h"
#include "Defines.h"
#include "BaseActionCharacter.h"
#include "AI/Controller/BaseAIController.h"
#include "Equipment/BaseWeapon.h"
#include "Table/ActionDataTable.h"

const FName SELFACTOR = TEXT("SelfActor");

void UBTT_BaseAnimation::PlayAnimation(ABaseEnemyCharacter* character, UBehaviorTreeComponent& OwnerComp, ECharacterCombatMontageType animSlot, float playRate)
{
	ABaseAIController* aiController = character->GetInstigatorController<ABaseAIController>();
	if (aiController)
	{
		UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();
		UE_LOG(LogTemp,Log, TEXT("dDD : %s"), *bbc->GetValueAsName(GetSelectedBlackboardKey()).ToString())
		aiController->SetActionTableData(bbc->GetValueAsName(GetSelectedBlackboardKey()));

		ABaseWeapon* weapon = Cast<ABaseWeapon>(character->GetCombatComponent()->GetEquipment(ECombatEquipmentSlot::E_MainWeapon));
		const FActionTable* tableData = aiController->GetActionTableData();
		if (tableData)
			weapon->SetDamageType(tableData->damageType.GetDefaultObject());
		else
			weapon->SetDamageType(Cast<UDamageType>(UDamageType::StaticClass()->GetDefaultObject()));
	}
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
	ABaseActionCharacter* selfActor = Cast<ABaseActionCharacter>(bbc->GetValueAsObject(SELFACTOR));
	float dis = FVector::DistSquared(selfActor->GetActorLocation(), target->GetTargetLocation());

	const FAIPatternDataTable& aiPatternData = patternData->GetPatternData();

	float conditionDis = aiPatternData.condition.distance;
	float powConditionDis = conditionDis * conditionDis;

	if (powConditionDis < dis)
		return false;

	const TSharedPtr<FStatusData>& statusData = selfActor->GetCombatComponent()->GetStatusData().GetStatusData();
	float present = StaticCast<float>(StaticCast<float>(statusData->health) / StaticCast<float>(statusData->maxHealth));

	if (aiPatternData.condition.hpPresent < present)
		return false;

	return true;
}
