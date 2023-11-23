// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/DodgeState.h"
#include "HFSM/States/PlayerStateEnum.h"
#include "Player/PlayerCharacter.h"
#include "Character/PlayerCommonEnums.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "HFSM/PlayerStateMachineEnum.h"
#include "HFSM/StateMachine.h"
#include "DebugLog.h"

FDodgeState::FDodgeState() : 
	FState(StaticCast<uint8>(EPlayerStateEnum::Dodge))
{
}

FDodgeState::~FDodgeState()
{
}

void FDodgeState::Enter()
{
	isDodgeEnd = false;
	APlayerCharacter* player = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	if (player)
	{

		UCharacterCombatComponent* characterCombatComponent = player->GetCombatComponent();
		if (characterCombatComponent)
		{
			ECharacterCombatontageType type;
			EPlayerStateMachine stateMachine = player->GetCurrentStateMachineID<EPlayerStateMachine>();
			if (stateMachine == EPlayerStateMachine::Combat)
				type = StaticCast<ECharacterCombatontageType>(EPlayerCombatEnums::CombatDodge);
			else
				type = StaticCast<ECharacterCombatontageType>(EPlayerCombatEnums::NomalDodge);

			characterCombatComponent->Dodge(type, [this]()
				{
					this->isDodgeEnd = true;
				}
			);
		}
	}
}

uint8 FDodgeState::Condition()
{
	uint8 stateid = FState::Condition();
	if (isDodgeEnd)
	{
		stateid = StaticCast<uint8>(EPlayerStateEnum::Idle);
	}
	return stateid;
}
