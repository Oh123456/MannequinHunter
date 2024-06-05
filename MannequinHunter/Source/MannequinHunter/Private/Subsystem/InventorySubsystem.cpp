// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/InventorySubsystem.h"

const int UInventorySubsystem::MAX_ITEM_COUNT = 84;

UInventorySubsystem::UInventorySubsystem() :  Super()
{
	items.Reset(MAX_ITEM_COUNT);
}

void UInventorySubsystem::SetItemData(const int32 index, const FITemData& data)
{
	if (index >= MAX_ITEM_COUNT)
		return;
	items[index] = data;
}

const FITemData* UInventorySubsystem::GetItemData(const int32 index) const
{
	if (index >= MAX_ITEM_COUNT)
		return nullptr;
	return &items[index];
}

void UInventorySubsystem::Reset()
{
	items.Reset();
}
