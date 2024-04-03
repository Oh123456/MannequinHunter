// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MannequinHunterPlayerController.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/ActionDataTable.h"

void AMannequinHunterPlayerController::SetActionTableData(const FName& actionName)
{
	tableData = actionTable->FindRow<FActionTable>(actionName, TEXT(""));
}

void AMannequinHunterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTableSubsystem* tableSubsystem = GetGameInstance()->GetSubsystem<UTableSubsystem>();

	actionTable = tableSubsystem->GetTable<FActionTable>();
}


