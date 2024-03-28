// Fill out your copyright notice in the Description page of Project Settings.


#include "HFSM/RYUHFSMComponent.h"
#include "HFSM/StateMachine.h"
#include "Character/RYU.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "HFSM/StatesMachines/DefaultStateMachine.h"
#include "HFSM/StatesMachines/CombatStateMachine.h"
#include "HFSM/StatesMachines/FallingStateMachine.h"
#include "HFSM/StatesMachines/HitStateMachine.h"
#include "HFSM/StatesMachines/DeathStateMachine.h"
#include "DebugLog.h"

void URYUHFSMComponent::SetStateMachine()
{
	defaultStateID = StaticCast<uint8>(EPlayerStateMachine::Default);

	TSharedPtr<FStateMachine>* stateMachine = AddStateMachine<FDefaultStateMachine>(EPlayerStateMachine::Default);

	stateMachine = AddStateMachine<FCombatStateMachine>(EPlayerStateMachine::Combat);

	stateMachine = AddStateMachine<FFallingStateMachine>(EPlayerStateMachine::Falling);

	stateMachine = AddStateMachine<FHitStateMachine>(EPlayerStateMachine::Hit);

	stateMachine = AddStateMachine<FDeathStateMachine>(EPlayerStateMachine::Death);
}

void URYUHFSMComponent::SetConditions()
{

	TSharedPtr<FStateMachine>* stateMachine = FindStateMachine(EPlayerStateMachine::Default);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeFalling);

	stateMachine = FindStateMachine(EPlayerStateMachine::Combat);
	(*stateMachine)->AddStateCondition(this, &URYUHFSMComponent::ChangeFalling);


	stateMachine = FindStateMachine(EPlayerStateMachine::Falling);
	(*stateMachine)->AddUpdateStateCondition(this, &URYUHFSMComponent::ChangeFallingEnd);
}


void URYUHFSMComponent::ChangeCombat(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(GetCurrentStateMachineID());
	
	if (order == StaticCast<uint16>(EStateOrder::ToggleCombat))
	{
		if (IsCombat())
			result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Default));
		else
			result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Combat));
	}

}

void URYUHFSMComponent::ChangeFalling(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(GetCurrentStateMachineID());

	uint16 fallingStateOrderID = StaticCast<uint16>(EStateOrder::Falling);
	
	if (order == fallingStateOrderID)
	{
		EPlayerStateMachine eStateMachine = StaticCast<EPlayerStateMachine>(result.stateID);
		if (eStateMachine == EPlayerStateMachine::Combat ||
			eStateMachine == EPlayerStateMachine::Default)
		{
			result.SetStateID(StaticCast<uint16>(EPlayerStateMachine::Falling));
		}
	}
}

void URYUHFSMComponent::ChangeFallingEnd(uint16 order, OUT FStateMachineConditionResult& result)
{
	if (result.isChange)
		return;
	result.SetDefaultStateID(GetCurrentStateMachineID());

	if (!ryuCharacter->GetMovementComponent()->IsFalling())
	{
		if (IsCombat())
			result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Combat));
		else
			result.SetStateID(StaticCast<uint8>(EPlayerStateMachine::Default));
	}
}

void URYUHFSMComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ryuCharacter = static_cast<ARYU*>(GetOwner());
}
