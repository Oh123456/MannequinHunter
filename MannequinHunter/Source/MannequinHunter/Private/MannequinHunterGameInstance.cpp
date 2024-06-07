// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinHunterGameInstance.h"
#include "Subsystem/CommandListSubsystem.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/MannequinHunterStatusTable.h"
#include "Table/ItemDataTable.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Subsystem/InventorySubsystem.h"


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
	const UDataTable* itemDataTable = tableSubsystem->GetTable<FItemTable>();
	FName itemID = TEXT("Sword01");

	FItemData itemData(itemID, itemDataTable->FindRow<FItemTable>(itemID, TEXT("")));
	inventorySubsystem->SetItemData(index++, itemData);

	itemID = TEXT("Sword02");
	itemData = FItemData(itemID, itemDataTable->FindRow<FItemTable>(itemID, TEXT("")));
	inventorySubsystem->SetItemData(index++, itemData);

	itemID = TEXT("Fist01");
	itemData = FItemData(itemID, itemDataTable->FindRow<FItemTable>(itemID, TEXT("")));
	inventorySubsystem->SetItemData(index++, itemData);

	itemID = TEXT("Fist02");
	itemData = FItemData(itemID, itemDataTable->FindRow<FItemTable>(itemID, TEXT("")));
	inventorySubsystem->SetItemData(index++, itemData);
}
