#include "Item/Item.h"
#include "Table/ItemDataTable.h"
#include "Subsystem/TableSubsystem.h"

FItemData::FItemData(const FName& itemID, const FItemTable* tableData) :
	id(itemID) , type()
{
	type = tableData->itemType;
}

FEquipmentItemData::FEquipmentItemData(const FName& itemID, const FItemTable* tableData)
	: FItemData(itemID, tableData)
{
	const FEquipmentItemTable* equipmentItemTable = (const FEquipmentItemTable*)(tableData);
	statusData = equipmentItemTable->statusData;
	weaponConstant = equipmentItemTable->weaponConstant;
}

TSharedPtr<FItemData> FItemFactory::CreateItemData(const FName& itemID, UTableSubsystem* tableSubsystem)
{
	if (tableSubsystem == nullptr)
		return nullptr;

	FItemDataTableResult result;
	tableSubsystem->GetItemTable(itemID , result);
	const UDataTable* tableData = result.table;
	FItemTable* table = nullptr;
	switch (result.type)
	{
	case EItemType::E_Etc:
	{
		table = tableData->FindRow<FItemTable>(itemID, TEXT(""));
		return MakeShared<FItemData>(itemID, table);
	}
	case EItemType::E_Equipment:
	{
		table = tableData->FindRow<FEquipmentItemTable>(itemID, TEXT(""));
		return MakeShared<FEquipmentItemData>(itemID, table);
	}
	case EItemType::E_Weapon:
	{
		table = tableData->FindRow<FEquipmentItemTable>(itemID, TEXT(""));
		return MakeShared<FWeaponItemData>(itemID, table);
	}
	default:
		return nullptr;
	}
}
