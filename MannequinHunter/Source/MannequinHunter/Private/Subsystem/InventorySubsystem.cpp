// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/InventorySubsystem.h"
#include "Table/ItemDataTable.h"
#include "Subsystem/TableSubsystem.h"

const int UInventorySubsystem::MAX_ITEM_COUNT = 84;

UInventorySubsystem::UInventorySubsystem() :  Super()
{
	items.Reset(MAX_ITEM_COUNT);
	for (int i = 0; i < MAX_ITEM_COUNT; i++)
	{
		items.Add(FItemData());
	}
}

void UInventorySubsystem::SetItemData(const int32 index, const FItemData& data)
{
	if (index >= MAX_ITEM_COUNT)
		return;
	items[index] = data;
}

void UInventorySubsystem::SetItemData(const int32 index, const FName& itemID)
{
	UTableSubsystem* tableSubsystem = GetGameInstance()->GetSubsystem<UTableSubsystem>();
	const UDataTable* itemDataTable = tableSubsystem->GetTable<FItemTable>();
	SetItemData(index, FItemData(itemID, itemDataTable->FindRow<FItemTable>(itemID, TEXT(""))));
}

const FItemData* UInventorySubsystem::GetItemData(const int32 index) const
{
	if (index >= MAX_ITEM_COUNT)
		return nullptr;
	return &items[index];
}

void UInventorySubsystem::Reset()
{
	items.Reset();
}

FItemData::FItemData(const FName& itemID, const FItemTable* tableData) : 
	id(itemID) , statusData()
{
	statusData = tableData->statusData;
}
