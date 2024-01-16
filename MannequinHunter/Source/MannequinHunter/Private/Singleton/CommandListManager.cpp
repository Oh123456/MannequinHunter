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
	//commandListMap.Empty();
}


//void FCommandListManager::LoadCommandListTable(const TMap<EWeaponType, TObjectPtr<UDataTable>>& table )
//{
//
//	commandListMap.Reset();
//
//	for (const auto& pair : table)
//	{
//		TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>> commandListTree = MakeShared<TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>>();
//
//
//		TArray<FName> names = pair.Value->GetRowNames();
//		for (const FName& name : names)
//		{
//			FCommandDataTable* table = pair.Value->FindRow<FCommandDataTable>(name, TEXT(""));
//			AddCommandListTree(commandListTree,table);
//		}
//
//		commandListMap.Add(pair.Key, commandListTree);
//
//	}
//
//}
//
//const TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>>* FCommandListManager::GetCommandList(EWeaponType weaponType) const
//{
//	return commandListMap.Find(weaponType);
//}
//
//void FCommandListManager::AddCommandListTree(const TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>>& tree, const FCommandDataTable* table)
//{
//	using CommandListNode = TCommandListNode<EPlayerInputType, ECharacterCombatMontageType>;
//
//	const TArray<EPlayerInputType>& inputTypes = table->attackButton;
//	TSharedPtr<CommandListNode>* node = nullptr;
//	int32 maxCount = inputTypes.Num();
//	ECharacterCombatMontageType* value = nullptr;
//	ECharacterCombatMontageType useAnimSlot = table->useAnimSlot;
//	for(int i = 0 ; i < maxCount; i++)
//	{
//		if (i == (maxCount - 1))
//			value = &useAnimSlot;
//		node = tree->AddTree(inputTypes[i], value, node);
//	}
//
//
//}

void FCommandListManager::LoadCommandListTable(const UDataTable* table )
{

	TArray<FName> names = table->GetRowNames();
	for (const FName& name : names)
	{
		FCommandDataTable* rowTable = table->FindRow<FCommandDataTable>(name, TEXT(""));
		AddCommandListTree(rowTable);
	}
	

}

void FCommandListManager::AddCommandListTree(const FCommandDataTable* table)
{
	using CommandListNode = TCommandListNode<EPlayerInputType, ECharacterCombatMontageType>;

	const TArray<EPlayerInputType>& inputTypes = table->attackButton;
	TSharedPtr<CommandListNode>* node = nullptr;
	int32 maxCount = inputTypes.Num();
	ECharacterCombatMontageType* value = nullptr;
	ECharacterCombatMontageType useAnimSlot = table->useAnimSlot;
	for (int i = 0; i < maxCount; i++)
	{
		if (i == (maxCount - 1))
			value = &useAnimSlot;
		node = commandList.AddTree(inputTypes[i], value, node);
	}
}