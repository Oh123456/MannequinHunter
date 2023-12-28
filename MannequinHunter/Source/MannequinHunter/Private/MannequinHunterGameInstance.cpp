// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinHunterGameInstance.h"
#include "Singleton/CommandListManager.h"
#include "Singleton/TableManager.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"

void UMannequinHunterGameInstance::OnStart()
{
	Super::OnStart();

	//�ӽ�
	FTableManager* tableManager = FTableManager::GetInstance();
	FCommandListManager::GetInstance()->LoadCommandListTable((tableManager->GetTable<FCommandDataTable>()));
}
