// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinHunterGameInstance.h"
#include "Singleton/CommandListManager.h"

void UMannequinHunterGameInstance::OnStart()
{
	Super::OnStart();


	FCommandListManager::GetInstance()->LoadCommandListTable(commendDataTable);
}
