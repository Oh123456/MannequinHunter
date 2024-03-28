// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Subsystem/CommandListSubsystem.h"
#include "Player/PlayerCharacter.h"
#include "HFSM/HFSMComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "Utility/MannequinHunterUtility.h"
#ifdef UE_BUILD_DEBUG
#include "Character/RYU.h"
#include "Utility/PlayerInputLog.h"
#endif

UMannequinHunterCombatComponent::~UMannequinHunterCombatComponent()
{

}

void UMannequinHunterCombatComponent::ResetCommandList()
{
	commandListData.currentCommandListNode = GetWorld()->GetGameInstance()->GetSubsystem<UCommandListSubsystem>()->GetCommandList().GetRoot();

	//commandListData.currentCommandListNode = FCommandListManager::GetInstance()->GetCommandList().GetRoot();
}

const ECharacterCombatMontageType UMannequinHunterCombatComponent::GetCommandMontageType()
{
#ifdef UE_BUILD_DEBUG
	ARYU* ryu = Cast<ARYU>(GetOwner());
	if (ryu)
	{
		ryu->GetPlayerInputLog()->AddPlayerInput(commandListData.playerInputType);
	}
#endif
	return GetCommandMontageType(commandListData.playerInputType);
}

const ECharacterCombatMontageType UMannequinHunterCombatComponent::GetCommandMontageType(EPlayerInputType input)
{
	
	const TSharedPtr<CommandListNode>& currentCommandListNode = commandListData.currentCommandListNode;
	if (currentCommandListNode)
	{
		const TSharedPtr<CommandListNode>* nextCommandListNode =  currentCommandListNode->FindChild(input);
		if (nextCommandListNode)
		{
			commandListData.currentCommandListNode = *nextCommandListNode;
			return *(*commandListData.currentCommandListNode->GetValue());
		}
	}

	return ECharacterCombatMontageType::None;
}

void UMannequinHunterCombatComponent::SetCommandList()
{
	commandListData.currentCommandListNode = GetWorld()->GetGameInstance()->GetSubsystem<UCommandListSubsystem>()->GetCommandList().GetRoot();
	//commandListData.currentCommandListNode = FCommandListManager::GetInstance()->GetCommandList().GetRoot();
}

void UMannequinHunterCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetCommandList();

	APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner());
	if (player == nullptr)
		return;

	ownerHFSM = player->GetHFSM();
}

void UMannequinHunterCombatComponent::Hit(ECharacterCombatMontageType animtype)
{
	Super::Hit(animtype);

	ownerHFSM->SetStateOrder(EStateOrder::StatemMachineHit | EStateOrder::Hit);
}

void UMannequinHunterCombatComponent::OnHitEnd()
{
	ownerHFSM->SetStateOrder(EStateOrder::Combat | EStateOrder::Idle);
}

int32 UMannequinHunterCombatComponent::CalculateRecoveryStamina()
{
	int32 recoveryStaminaValue = Super::CalculateRecoveryStamina();

	if (ownerHFSM->GetCurrentStateID() != StaticCast<uint8>(EPlayerStateEnum::Idle))
	{
		recoveryStaminaValue = recoveryStaminaValue * 0.5f;
	}

	return recoveryStaminaValue;
}

float UMannequinHunterCombatComponent::GetPlayRate(UAnimInstance* animInstance)
{
	return FMannequinHunterUtility::GetPlayRate(GetStatusData().GetStatusData()->attackSpeed);
}

void UMannequinHunterCombatComponent::Death(const FDeathInfo& deathInfo)
{
	ownerHFSM->ChangeStateMachine(StaticCast<uint8>(EPlayerStateMachine::Death));

	Super::Death(deathInfo);

}


