// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinHunterGameInstance.h"
#include "Singleton/CommandListManager.h"
#include "Singleton/TableManager.h"
#include "Table/MannequinHunterStatusTable.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"


void UMannequinHunterGameInstance::OnStart()
{
	Super::OnStart();

	//юс╫ц
	FTableManager* tableManager = FTableManager::GetInstance();
	FCommandDataTable::StaticStruct();
	FCommandListManager::GetInstance()->LoadCommandListTable((tableManager->GetTable<FCommandDataTable>()));
}
