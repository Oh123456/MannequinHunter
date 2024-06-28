// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageType/RecoveryStaminaDamageType.h"
#include "Utility/MannequinHunterTags.h"
#include "Controller/MannequinHunterPlayerController.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "BaseActionCharacter.h"
#include "Table/ActionDataTable.h"

void URecoveryStaminaDamageType::ChangeStatus(AController* eventInstigator)
{
	AMannequinHunterPlayerController* controller = Cast<AMannequinHunterPlayerController>(eventInstigator);

	if (controller == nullptr)
		return;

	ABaseActionCharacter* character = Cast<ABaseActionCharacter>(controller->GetPawn());
	if (character == nullptr)
		return;

	if (character->ActorHasTag(MannequinHnterTags::PLAYER))
	{
		UMannequinHunterCombatComponent* combatComponent = Cast<UMannequinHunterCombatComponent>(character->GetCombatComponent());
		const FActionTable* table = controller->GetActionTableData();

		FStatus& status = combatComponent->GetStatusData();
		
		status.AddStamina(table->actionDataMap[combatComponent->GetWeaponType()].recoveryStamina);
	}
}
