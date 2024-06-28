// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Subsystem/CommandListSubsystem.h"
#include "Player/PlayerCharacter.h"
#include "HFSM/HFSMComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "Utility/MannequinHunterUtility.h"
#include "Controller/MannequinHunterPlayerController.h"
#include "Table/ActionDataTable.h"
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

const TSharedPtr<FCommandData>* UMannequinHunterCombatComponent::GetCommandMontageType()
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

const TSharedPtr<FCommandData>* UMannequinHunterCombatComponent::GetCommandMontageType(EPlayerInputType input)
{
	
	const TSharedPtr<CommandListNode>& currentCommandListNode = commandListData.currentCommandListNode;
	if (currentCommandListNode)
	{
		const TSharedPtr<CommandListNode>* nextCommandListNode =  currentCommandListNode->FindChild(input);
		if (nextCommandListNode)
		{
			commandListData.currentCommandListNode = *nextCommandListNode;
			return (commandListData.currentCommandListNode->GetValue());
		}
	}

	return nullptr;
}

void UMannequinHunterCombatComponent::SetCommandList()
{
	commandListData.currentCommandListNode = GetWorld()->GetGameInstance()->GetSubsystem<UCommandListSubsystem>()->GetCommandList().GetRoot();
}

bool UMannequinHunterCombatComponent::CheckStatus()
{
	AMannequinHunterPlayerController* controller = GetOwner()->GetInstigatorController<AMannequinHunterPlayerController>();
	const FActionTable* data = controller->GetActionTableData();

	const FActionTableData* tableData = data->actionDataMap.Find(commandListData.playerWeaponType);

	if (tableData == nullptr)
		return false;

	int32 stamina = tableData->useStamina;
	if (!status.CheckStamina())
		return false;

	status.AddStamina(-stamina);

	isSuperArmor = tableData->isSuperArmor;
	isImmortality = tableData->isImmortality;
	return true;
}

float UMannequinHunterCombatComponent::CalculateApplyDamage()
{
	float damage = Super::CalculateApplyDamage();
	AMannequinHunterPlayerController* controller = GetOwner()->GetInstigatorController<AMannequinHunterPlayerController>();
	if (controller->GetActionTableData() != nullptr)
		damage *= controller->GetActionTableData()->damageCoefficient;
	return damage;
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

void UMannequinHunterCombatComponent::Dodge(ECharacterCombatMontageType animtype, float playRate, std::function<void()> endcallback, std::function<void()> cancelCallback)
{
	//묶던지 합시다
	if (!CheckStatus())
		return;
	Super::Dodge(animtype, playRate, endcallback, cancelCallback);
}

void UMannequinHunterCombatComponent::Attack(ECharacterCombatMontageType animtype, float playRate, std::function<void()> endcallback, std::function<void()> cancelCallback)
{
	if (!CheckStatus())
		return;

	Super::Attack(animtype, playRate, endcallback, cancelCallback);
}


