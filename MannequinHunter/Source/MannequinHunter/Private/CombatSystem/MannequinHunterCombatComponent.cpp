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
	if (commandListData.currentCommandListTree)
		commandListData.currentCommandListNode = commandListData.currentCommandListTree->GetRoot();
}

ECharacterCombatMontageType UMannequinHunterCombatComponent::GetCommandMontageType()
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

ECharacterCombatMontageType UMannequinHunterCombatComponent::GetCommandMontageType(EPlayerInputType input)
{
	const TSharedPtr<CommandListTree>& currentCommandListTree = commandListData.currentCommandListTree;
	const TSharedPtr<CommandListNode>& currentCommandListNode = commandListData.currentCommandListNode;
	if (currentCommandListTree && currentCommandListNode)
	{
		const TSharedPtr<CommandListNode>* nextCommandListNode =  currentCommandListNode->FindChild(input);
		if (nextCommandListNode)
		{
			commandListData.currentCommandListNode = *nextCommandListNode;
			return *(commandListData.currentCommandListNode->GetValue()->Get());
		}
	}
	return ECharacterCombatMontageType::None;
}

void UMannequinHunterCombatComponent::ChangeCommandList(EWeaponType type)
{
	commandListData.currentCommandListTree = *FCommandListManager::GetInstance()->GetCommandList(type);
	commandListData.currentCommandListNode = commandListData.currentCommandListTree->GetRoot();
}

void UMannequinHunterCombatComponent::BeginPlay()
{
	Super::BeginPlay();


	OnChangeWeaponType.AddUObject(this,&UMannequinHunterCombatComponent::ChangeCommandList);
}


