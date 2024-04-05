// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageType/RecoveryStaminaDamageType.h"
#include "Utility/MannequinHunterTags.h"
#include "Controller/MannequinHunterPlayerController.h"
#include "CombatSystem/CharacterCombatComponent.h"
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

		const FActionTable* table = controller->GetActionTableData();

		FStatus& status = character->GetCombatComponent()->GetStatusData();
		
		status.AddStamina(table->recoveryStamina);
	}
}
