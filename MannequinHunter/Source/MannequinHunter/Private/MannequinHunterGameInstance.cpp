// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinHunterGameInstance.h"
#include "Singleton/CommandListManager.h"
#include "Singleton/TableManager.h"

void UMannequinHunterGameInstance::OnStart()
{
	Super::OnStart();

	//юс╫ц
	FTableManager::GetInstance();
	FCommandListManager::GetInstance()->LoadCommandListTable(commendDataTable);
}
