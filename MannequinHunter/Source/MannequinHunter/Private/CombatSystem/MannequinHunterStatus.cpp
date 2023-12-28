// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/MannequinHunterStatus.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"

void FMannequinHunterStatus::CreateStatus()
{
	status = MakeShared<FMannequinHunterStatusData>();
}

const FStatusDataBase* FMannequinHunterStatus::GetStatusDataFormTable(const FStatusDataTableBase* dataTable)
{
	const FMannequinHunterStatusDataTable* table = StaticCast<const FMannequinHunterStatusDataTable*>(dataTable);

	if (!table)
		return nullptr;

	return &table->statusData;
}

