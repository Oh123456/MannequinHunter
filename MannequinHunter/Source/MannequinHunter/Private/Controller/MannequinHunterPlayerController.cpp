// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MannequinHunterPlayerController.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/ActionDataTable.h"

void AMannequinHunterPlayerController::SetActionTableData(const FName& actionName)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *actionName.ToString())
	tableData = actionTable->FindRow<FActionTable>(actionName, TEXT("ActionTable Not Found"));
}

void AMannequinHunterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTableSubsystem* tableSubsystem = GetGameInstance()->GetSubsystem<UTableSubsystem>();

	actionTable = tableSubsystem->GetTable<FActionTable>();
}


