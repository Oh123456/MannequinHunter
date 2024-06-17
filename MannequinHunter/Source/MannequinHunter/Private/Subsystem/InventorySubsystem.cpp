// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/InventorySubsystem.h"
#include "Table/ItemDataTable.h"
#include "Subsystem/TableSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MannequinHunterPlayerCharacter.h"
#include "CombatSystem/PlayerCharacterCombatComponent.h"
#include "CombatSystem/MannequinHunterStatus.h"
#include "Item/Item.h"

const int UInventorySubsystem::MAX_ITEM_COUNT = 84;

UInventorySubsystem::UInventorySubsystem() :  Super()
{
	items.Reset(MAX_ITEM_COUNT);
	for (int i = 0; i < MAX_ITEM_COUNT; i++)
	{
		items.Add(nullptr);
	}

	Equipment(EEquipment::E_Weapone, nullptr);
	Equipment(EEquipment::E_Armor, nullptr);
	Equipment(EEquipment::E_Accessories, nullptr);
}

void UInventorySubsystem::SetItemData(const int32 index, const TSharedPtr<FItemData>& data)
{
	if (index >= MAX_ITEM_COUNT)
		return;
	items[index] = data;
	addInventoryEvent.Broadcast(data->id, index);
}

void UInventorySubsystem::SetItemData(const int32 index, const FName& itemID)
{
	UTableSubsystem* tableSubsystem = GetGameInstance()->GetSubsystem<UTableSubsystem>();
	SetItemData(index, FItemFactory::CreateItemData(itemID, tableSubsystem));
}

int32 UInventorySubsystem::FindEmptySlot()
{
	for (int32 i = 0; i < MAX_ITEM_COUNT; i++)
	{
		if (items[i] == nullptr || 
			items[i]->id.IsNone())
			return i;
	}
	return -1;
}

void UInventorySubsystem::Equipment(EEquipment slot, const TSharedPtr<FItemData>& data)
{
	if (equipment.Contains(slot))
		equipment[slot] = data;
	else
		equipment.Add(slot, data);

	
	AMannequinHunterPlayerCharacter* player = Cast<AMannequinHunterPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (data && player)
	{
		FStatus& status = player->GetCombatComponent()->GetStatusData();
		status.Sum(data->GetStatusData());
	}
	equipmentEvent.Broadcast(slot, data);
}

void UInventorySubsystem::Equipment(EEquipment slot, int32 InventoryIndex)
{
	const TSharedPtr<FEquipmentItemData>& data = StaticCastSharedPtr<FEquipmentItemData>(items[InventoryIndex]);
	
	if (data == nullptr ||  data->id.IsNone())
		return;
	const TSharedPtr<FItemData> equipmentData = *equipment.Find(slot);
	
	equipment[slot] = data;
	items[InventoryIndex] = equipmentData;
	equipmentEvent.Broadcast(slot, data);

	AMannequinHunterPlayerCharacter* player = Cast<AMannequinHunterPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		FStatus& status = player->GetCombatComponent()->GetStatusData();
		FMannequinHunterStatusData statusData = data->GetStatusData();
		if (equipmentData)
			statusData.Sub(equipmentData->GetStatusData());
		status.Sum(statusData);
	}

	UE_LOG(LogTemp, Log, TEXT("weaponConstant!!!! %f "), data->GetWeaponConstant());
}

void UInventorySubsystem::RemoveEquipment(EEquipment slot)
{
	const TSharedPtr<FItemData> equipmentData = *equipment.Find(slot);

	if (equipmentData == nullptr || equipmentData->id.IsNone())
		return;

	equipment[slot] = nullptr;

	AMannequinHunterPlayerCharacter* player = Cast<AMannequinHunterPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		FStatus& status = player->GetCombatComponent()->GetStatusData();
		FMannequinHunterStatusData statusData = equipmentData->GetStatusData();
		status.Sub(statusData);
	}

}

const TSharedPtr<FItemData>* UInventorySubsystem::GetItemData(const int32 index) const
{
	if (index >= MAX_ITEM_COUNT)
		return nullptr;
	return &items[index];
}

void UInventorySubsystem::Reset()
{
	items.Reset();
}

