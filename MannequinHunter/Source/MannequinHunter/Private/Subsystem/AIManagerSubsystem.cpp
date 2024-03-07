// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/AIManagerSubsystem.h"
#include "Subsystem/TableSubsystem.h"
#include "DebugLog.h"
#include "../MannequinHunter.h"

void FPatternData::AddWeightArray(int32 weightValue)
{
	if (weightValue == 0)
		return;
	if (weightArray.Num() == 0)
		weightArray.Add(0);
	weightArray.Add(weightValue);
}

const TSharedPtr<FAIPatternTree> UAIManagerSubsystem::GetPattern(const FName& tableName) const
{
	const TSharedPtr<FAIPatternTree>* findPattern = AIPatternMap.Find(tableName);
	if (findPattern == nullptr)
	{

	}

	return nullptr;
}

void UAIManagerSubsystem::LoadPattern(const FName& tableRowName)
{
	UTableSubsystem* tableSubsystem = GetGameInstance()->GetSubsystem<UTableSubsystem>();

	const UDataTable* patternTreeTable = tableSubsystem->GetTable<FAIPatternTreeTable>();

	FAIPatternTreeTable* row = patternTreeTable->FindRow<FAIPatternTreeTable>(tableRowName, TEXT("Check AIPatternTreeTable"));
	if (row == nullptr)
		return;

	const UDataTable* patternTable = tableSubsystem->LoadAIPatternTable(row->patternDataTableName);

	if (patternTable == nullptr)
	{
		UE_LOG_WARNING(GameInstanceSubsystem, TEXT("%s Check Table"), *row->patternDataTableName.ToString());
		return;
	}

	TSharedPtr<FAIPatternTree> AIPatternTree = MakeShared<FAIPatternTree>();


	for (auto& patternDataPair : row->patternData)
	{
		;
		 
		TTree<FName, FPatternData>& addedTree = AIPatternTree->patternTrees.Add(patternDataPair.Key, TTree<FName, FPatternData>());
		for (const FAIPatternTreeTableData& data : patternDataPair.Value.datas)
		{
			data.data.patternName;

			FAIPatternDataTable* aiPatternData = patternTable->FindRow<FAIPatternDataTable>(data.data.patternName, TEXT(""));
			if (aiPatternData == nullptr)
				continue;

			FPatternData patternData;
			patternData.SetPatternData(*aiPatternData, data.data.weight);


			addedTree.AddRootChilde(aiPatternData->patternName, &patternData);

			//넓이 우선이 좋을듯..
		}
	}


	//AIPatternMap.Add(tableRowName)
}
