// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/DodgeState.h"
#include "Character/PlayerCommonEnums.h"
#include "Player/PlayerCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "HFSM/StateMachine.h"
#include "Controller/MannequinHunterPlayerController.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "DebugLog.h"
#include "Utility/MannequinHunterUtility.h"

FDodgeState::FDodgeState() : 
	FBaseMannequinHunterState(StaticCast<uint8>(EPlayerStateEnum::Dodge), EStateInitOption::UpdataAndConvertOrder)
{
	convertOrder->Add(StaticCast<uint16>(EStateOrder::Idle));
	convertOrder->Add(StaticCast<uint16>(EStateOrder::InputWait));
}

FDodgeState::~FDodgeState()
{
}

void FDodgeState::Enter()
{

	APlayerCharacter* player = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	if (player)
	{
		UCharacterCombatComponent* characterCombatComponent = player->GetCombatComponent();
		if (characterCombatComponent)
		{
			ECharacterCombatMontageType type;
			EPlayerStateMachine stateMachine = player->GetCurrentStateMachineID<EPlayerStateMachine>();
			if (stateMachine == EPlayerStateMachine::Combat)
				type = StaticCast<ECharacterCombatMontageType>(EPlayerCombatEnums::CombatDodge);
			else
				type = StaticCast<ECharacterCombatMontageType>(EPlayerCombatEnums::NomalDodge);

			AMannequinHunterPlayerController* controller = ownerStateMachine->GetOwnerCharacter()->GetController<AMannequinHunterPlayerController>();

			// ÀÓ½Ã °ª
			if (controller)
			{
				if (stateMachine == EPlayerStateMachine::Combat)
					controller->SetActionTableData(TEXT("Combat_Dodge"));
				else
					controller->SetActionTableData(TEXT("Dodge"));
			}
			UMannequinHunterCombatComponent* mannequinHunterCombatComponent = Cast<UMannequinHunterCombatComponent>(player->GetCombatComponent());
			mannequinHunterCombatComponent->ResetCommandList();

			characterCombatComponent->Dodge(type, FMannequinHunterUtility::GetPlayRate(characterCombatComponent->GetStatusData().GetStatusData()->attackSpeed));/*[this]()
				{
					this->isDodgeEnd = true;
				}
			)*/
		}
	}
}

void FDodgeState::Exit()
{
	AMannequinHunterPlayerController* controller = ownerStateMachine->GetOwnerCharacter()->GetController<AMannequinHunterPlayerController>();

}

uint8 FDodgeState::Condition(uint16 order)
{
	uint8 stateid = FState::Condition(order);

	if (convertOrder->Contains(order))
	{
		if (order == StaticCast<uint16>(EStateOrder::InputWait))
		{
			stateid = StaticCast<uint16>(EPlayerStateEnum::InputWait);
			return stateid;
		}
		APlayerCharacter* player = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
		if (!player->IsMoveInput())
			stateid = StaticCast<uint16>(EPlayerStateEnum::Idle);
		else
			stateid = StaticCast<uint16>(EPlayerStateEnum::Move);
	}

	return stateid;
}


