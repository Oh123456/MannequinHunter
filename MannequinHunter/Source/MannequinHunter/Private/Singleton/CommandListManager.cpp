// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/CommandListManager.h"
#include "Engine/DataTable.h"
#include "Character/PlayerCommonEnums.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"

FCommandListManager::FCommandListManager()
{
}

FCommandListManager::~FCommandListManager()
{
}

//void FCommandListManager::LoadCommandListTable(UDataTable* table)
//{
//}
//
//void FCommandListManager::AddCommandListTree(const TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatontageType>>, const TArray<EPlayerInputType>&)
//{
//}
//


void FCommandListManager::LoadCommandListTable(const TMap<ERYUWeaponType, TObjectPtr<UDataTable>>& table )
{

	commandList.Reset();

	for (const auto& pair : table)
	{
		TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatontageType>> commandListTree = MakeShared<TCommandListTree<EPlayerInputType, ECharacterCombatontageType>>();


		TArray<FName> names = pair.Value->GetRowNames();
		for (const FName& name : names)
		{
			FCommandDataTable* table = pair.Value->FindRow<FCommandDataTable>(name, TEXT(""));
			AddCommandListTree(commandListTree,table);
		}

		commandList.Add(pair.Key, commandListTree);

	}

}

void FCommandListManager::AddCommandListTree(const TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatontageType>>& tree, const FCommandDataTable* table)
{
	using CommandListNode = TCommandListNode<EPlayerInputType, ECharacterCombatontageType>;

	const TArray<EPlayerInputType>& inputTypes = table->attackButton;
	TSharedPtr<CommandListNode>* node = nullptr;
	for (EPlayerInputType inputType : inputTypes)
	{
		node = tree->AddTree(inputType, MakeShared<ECharacterCombatontageType>(table->useAnimSlot), node);
	}

}

