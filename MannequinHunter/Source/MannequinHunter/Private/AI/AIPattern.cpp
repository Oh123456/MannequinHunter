// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPattern.h"
#include "Singleton/TableManager.h"


UAIPattern::~UAIPattern()
{
	tableData = nullptr;
}

void UAIPattern::LoadTableData()
{
	const UDataTable* table = FTableManager::GetInstance()->GetTable<FAIPatternTable>();
	if (table)
		tableData = table->FindRow<FAIPatternTable>(tableName, TEXT(""));
}

const FAIPatternData* UAIPattern::GetAIPatternData(FString patternKey) const
{
	if (tableData == nullptr)
		return nullptr;

	return tableData->patternData.Find(patternKey);
}
