// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/TableManager.h"
#include "Table/MannequinHunterStatusTable.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"

FTableManager::FTableManager()
{
	LoadTable<FMannequinHunterStatusDataTable>(TEXT("/Game/BP/DataTable/StatuesDataTable.StatuesDataTable"));
	
	//CommandTable/Script/Engine.DataTable'/Game/BP/DataTable/StatuesDataTable.StatuesDataTable'
	LoadTable<FCommandDataTable>(TEXT("/Game/BP/DataTable/CommandTable.CommandTable"));
}


FTableManager::~FTableManager()
{
	//tables.Empty();
	tableMap.Empty();
}


//void FTableManager::LoadTable(const TCHAR* name)
//{
//	UDataTable* findTable = LoadObject<UDataTable>(nullptr, name);
//
//	if (findTable)
//	{
//		
//	}
//	//	tables.Add(findTable);
//}
