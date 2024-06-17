// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinHunterGameInstance.h"
#include "Subsystem/CommandListSubsystem.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/MannequinHunterStatusTable.h"
#include "Table/ItemDataTable.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Subsystem/InventorySubsystem.h"
#include "Item/Item.h"

void UMannequinHunterGameInstance::OnStart()
{
	Super::OnStart();

	//юс╫ц

	

	//FTableManager* tableManager = FTableManager::GetInstance();
	//FCommandDataTable::StaticStruct();
	//FCommandListManager::GetInstance()->LoadCommandListTable((tableManager->GetTable<FCommandDataTable>()));
	UTableSubsystem* tableSubsystem = GetSubsystem<UTableSubsystem>();
	UCommandListSubsystem* commandListSubsystem = GetSubsystem<UCommandListSubsystem>();
	commandListSubsystem->LoadCommandListTable((tableSubsystem->GetTable<FCommandDataTable>()));

	UInventorySubsystem* inventorySubsystem = GetSubsystem<UInventorySubsystem>();
	int32 index = 0;
	FName itemID = TEXT("Sword01");
	inventorySubsystem->SetItemData(index++, FItemFactory::CreateItemData(itemID, tableSubsystem));

	itemID = TEXT("Sword02");
	inventorySubsystem->SetItemData(index++, FItemFactory::CreateItemData(itemID, tableSubsystem));

	itemID = TEXT("Fist01");
	inventorySubsystem->SetItemData(index++, FItemFactory::CreateItemData(itemID, tableSubsystem));

	itemID = TEXT("Fist02");
	inventorySubsystem->SetItemData(index++, FItemFactory::CreateItemData(itemID, tableSubsystem));

	itemID = TEXT("ETC_1");
	inventorySubsystem->SetItemData(index++, FItemFactory::CreateItemData(itemID, tableSubsystem));

	itemID = TEXT("ETC_2");
	inventorySubsystem->SetItemData(index++, FItemFactory::CreateItemData(itemID, tableSubsystem));

	itemID = TEXT("ETC_3");
	inventorySubsystem->SetItemData(index++, FItemFactory::CreateItemData(itemID, tableSubsystem));
}
