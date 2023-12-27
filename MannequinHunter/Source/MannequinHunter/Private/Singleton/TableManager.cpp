// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/TableManager.h"

#define Load(path)

FTableManager::FTableManager()
{
	LoadTable(TEXT("/Game/BP/DataTable/StatuesDataTable.StatuesDataTable"));
	
	// 커맨드리스트 테이블은 따로 관리 할것
	// 데이터 테이블 관리 수정?
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
