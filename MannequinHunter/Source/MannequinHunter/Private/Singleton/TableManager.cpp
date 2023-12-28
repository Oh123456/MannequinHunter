// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/TableManager.h"

#define Load(path)

FTableManager::FTableManager()
{
	LoadTable(TEXT("/Game/BP/DataTable/StatuesDataTable.StatuesDataTable"));
	
	//CommandTable
	LoadTable(TEXT("/Game/BP/DataTable/CommandTable.CommandTable"));
}


FTableManager::~FTableManager()
{
	tables.Empty();
}


void FTableManager::LoadTable(const TCHAR* name)
{
	UDataTable* findTable = LoadObject<UDataTable>(nullptr, name);

	if (findTable)
		tables.Add(findTable);
}
