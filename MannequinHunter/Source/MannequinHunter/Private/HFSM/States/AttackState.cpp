// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/AttackState.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/StateMachine.h"
#include "Player/PlayerCharacter.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "Singleton/StateManager.h"

FAttackState::FAttackState() : FState(StaticCast<uint8>( EPlayerStateEnum::Attack), EStateInitOption::DontUpdataAndConvertOrder)
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

ECharacterCombatMontageType FAttackState::GetAnimSlot()
{
	APlayerCharacter* player = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	UMannequinHunterCombatComponent* mannequinHunterCombatComponent = Cast<UMannequinHunterCombatComponent>(player->GetCombatComponent());
	if (mannequinHunterCombatComponent)
	{
		return mannequinHunterCombatComponent->GetCommandMontageType();
	}
	return ECharacterCombatMontageType::None;
}

void FAttackState::Enter()
{
	APlayerCharacter* player = StaticCast<APlayerCharacter*>(ownerStateMachine->GetOwnerCharacter());
	if (player)
	{
		UMannequinHunterCombatComponent* combatComponent = Cast<UMannequinHunterCombatComponent>(player->GetCombatComponent());
		
		if (combatComponent)
		{
			ECharacterCombatMontageType attackType = GetAnimSlot();

			if (attackType == ECharacterCombatMontageType::None)
				return;

			combatComponent->Attack(attackType, [this]()
			{
				this->CheckState();
			});
		}
	}
}

uint8 FAttackState::Condition(uint16 order)
{
	uint8 newState = FState::Condition(order);
	//if (order == StaticCast<uint16>(EStateOrder::Idle))
	if (convertOrder->Contains(order))
	{
		newState = FStateManager::GetInstance()->GetStateID(order); //StaticCast<uint8>(EPlayerStateEnum::Idle);
	}
	return newState;
}
