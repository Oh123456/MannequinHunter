// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/CommandListSubsystem.h"
#include "Engine/DataTable.h"
#include "Character/PlayerCommonEnums.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"

void UCommandListSubsystem::LoadCommandListTable(const UDataTable* table)
{
	TArray<FName> names = table->GetRowNames();
	for (const FName& name : names)
	{
		FCommandDataTable* rowTable = table->FindRow<FCommandDataTable>(name, TEXT(""));
		AddCommandListTree(rowTable);
	}
	
}

void UCommandListSubsystem::AddCommandListTree(const FCommandDataTable* table)
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

