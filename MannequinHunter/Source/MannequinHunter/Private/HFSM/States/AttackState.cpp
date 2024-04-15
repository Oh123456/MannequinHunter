// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/AttackState.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/StateMachine.h"
#include "Player/PlayerCharacter.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "Subsystem/StateSubsystem.h"
#include "CombatSystem/Status.h"
#include "Controller/MannequinHunterPlayerController.h"
#include "Utility/MannequinHunterUtility.h"
#include "Equipment/BaseWeapon.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/ActionDataTable.h"

FAttackState::FAttackState() : FBaseMannequinHunterState(StaticCast<uint8>( EPlayerStateEnum::Attack), EStateInitOption::DontUpdataAndConvertOrder) 
{
	convertOrder->Add(StaticCast<uint16>(EStateOrder::Idle));
	convertOrder->Add(StaticCast<uint16>(EStateOrder::InputWait));
}

FAttackState::~FAttackState()
{
}

void FAttackState::CheckState()
{
	ownerStateMachine->SetStateOrder(StaticCast<uint16>(EStateOrder::Idle));
}

const TSharedPtr<FCommandData>* FAttackState::GetAnimSlot()
{
	APlayerCharacter* player = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	UMannequinHunterCombatComponent* mannequinHunterCombatComponent = Cast<UMannequinHunterCombatComponent>(player->GetCombatComponent());
	if (mannequinHunterCombatComponent)
	{
		return (mannequinHunterCombatComponent->GetCommandMontageType());
	}
	return nullptr;
}

void FAttackState::Enter()
{
	APlayerCharacter* player = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	if (player)
	{
		UMannequinHunterCombatComponent* combatComponent = Cast<UMannequinHunterCombatComponent>(player->GetCombatComponent());
		
		if (combatComponent)
		{
			float playRate = FMannequinHunterUtility::GetPlayRate(combatComponent->GetStatusData().GetStatusData()->attackSpeed);
			
			UE_LOG(LogTemp, Log, TEXT("attackSpeed : %d  playRate : %f"), combatComponent->GetStatusData().GetStatusData()->attackSpeed,playRate);

			ABaseWeapon* weapon =Cast<ABaseWeapon>(combatComponent->GetEquipment(ECombatEquipmentSlot::E_MainWeapon));
			AMannequinHunterPlayerController* controller = ownerStateMachine->GetOwnerCharacter()->GetController<AMannequinHunterPlayerController>();
			const FActionTable* table = controller->GetActionTableData();
			if (table)
				weapon->SetDamageType(table->damageType.GetDefaultObject());
			else
				weapon->SetDamageType(Cast<UDamageType>(UDamageType::StaticClass()->GetDefaultObject()));

			combatComponent->Attack(attackMontageType, playRate,[this, combatComponent]()
			{
				this->CheckState();
			});
		}
	}
}

uint8 FAttackState::Condition(uint16 order)
{
	uint8 newState = FState::Condition(order);
	
	if (convertOrder->Contains(order))
	{
		newState = OrderToStateID(order);
	}
	return newState;
}

bool FAttackState::EnterCondition()
{
	bool isEnter = FState::EnterCondition();
	
	const TSharedPtr<FCommandData>* slot = GetAnimSlot();

	if (slot == nullptr || *slot == nullptr || (*slot)->useAnimSlot == ECharacterCombatMontageType::None)
		return false;

	attackMontageType = (*slot)->useAnimSlot;

	AMannequinHunterPlayerController* controller = ownerStateMachine->GetOwnerCharacter()->GetController<AMannequinHunterPlayerController>();

	if (controller)
		controller->SetActionTableData((*slot)->nameID);

	return isEnter;
}

void FAttackState::Exit()
{
	attackMontageType = ECharacterCombatMontageType::None;

}
