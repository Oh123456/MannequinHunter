// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPattern.h"
#include "Subsystem/TableSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AIPatternTable.h"


UAIPattern::~UAIPattern()
{
	tableData = nullptr;
}

void UAIPattern::LoadTableData(UWorld* world)
{
	UGameInstance* gameInstance = world->GetGameInstance();

	if (gameInstance)
	{
		const UDataTable* table = gameInstance->GetSubsystem<UTableSubsystem>()->GetTable<FAIPatternTreeTable>();
		if (table)
		{
			tableData = table->FindRow<FAIPatternTreeTable>(tableName, TEXT(""));
		}
	}
}

const FAIPatternTreeTableDataArray* UAIPattern::GetAIPatternData(float distance) const
{
	if (tableData == nullptr)
		return nullptr;

	return nullptr;
}
