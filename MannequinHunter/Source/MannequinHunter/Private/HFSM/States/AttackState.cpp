// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/States/AttackState.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/StateMachine.h"
#include "Player/PlayerCharacter.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "Singleton/StateManager.h"
#include "CombatSystem/Status.h"
#include "Utility/MannequinHunterUtility.h"

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
			float playRate = FMannequinHunterUtility::GetPlayRate(combatComponent->GetStatusData().GetStatusData()->attackSpeed);
			
			UE_LOG(LogTemp, Log, TEXT("attackSpeed : %d  playRate : %f"), combatComponent->GetStatusData().GetStatusData()->attackSpeed,playRate);

			combatComponent->Attack(attackMontageType, playRate,[this]()
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
		newState = FStateManager::GetInstance()->GetStateID(order); 
	}
	return newState;
}

bool FAttackState::EnterCondition()
{
	bool isEnter = FState::EnterCondition();
	
	attackMontageType = GetAnimSlot();

	if (attackMontageType == ECharacterCombatMontageType::None)
		isEnter = false;

	return isEnter;
}

void FAttackState::Exit()
{
	attackMontageType = ECharacterCombatMontageType::None;
}
