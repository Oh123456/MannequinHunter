// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPattern.h"
#include "Subsystem/TableSubsystem.h"
#include "Kismet/GameplayStatics.h"


UAIPattern::~UAIPattern()
{
	tableData = nullptr;
}

void UAIPattern::LoadTableData(UWorld* world)
{
	UGameInstance* gameInstance = world->GetGameInstance();

	if (gameInstance)
	{
		const UDataTable* table = gameInstance->GetSubsystem<UTableSubsystem>()->GetTable<FAIPatternTable>();//FTableManager::GetInstance()->GetTable<FAIPatternTable>();
		if (table)
		{
			tableData = table->FindRow<FAIPatternTable>(tableName, TEXT(""));

			FAIPatternTable* defaultTable = table->FindRow<FAIPatternTable>(TEXT("Default"), TEXT(""));
			if (defaultTable)
			{
				defaultWeight = defaultTable->patternData.begin().Value().datas[0].weight;
			}
		}
	}
}

const FAIPatternDataArray* UAIPattern::GetAIPatternData(float distance/*const FName& patternKey*/) const
{
	if (tableData == nullptr)
		return nullptr;

	return tableData->patternData.Find(distance);
}
