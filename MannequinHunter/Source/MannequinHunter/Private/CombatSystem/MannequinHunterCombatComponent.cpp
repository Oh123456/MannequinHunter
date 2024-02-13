// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Singleton/CommandListManager.h"
#ifdef UE_BUILD_DEBUG
#include "Character/RYU.h"
#include "Utility/PlayerInputLog.h"
#endif

UMannequinHunterCombatComponent::~UMannequinHunterCombatComponent()
{

}

void UMannequinHunterCombatComponent::ResetCommandList()
{
	commandListData.currentCommandListNode = FCommandListManager::GetInstance()->GetCommandList().GetRoot();
	//if (commandListData.currentCommandListTree)
	//	commandListData.currentCommandListNode = commandListData.currentCommandListTree->GetRoot();
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
	commandListData.currentCommandListNode = FCommandListManager::GetInstance()->GetCommandList().GetRoot();
}

void UMannequinHunterCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetCommandList();
	//OnChangeWeaponType.AddUObject(this,&UMannequinHunterCombatComponent::ChangeCommandList);
}


