// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/AIManagerSubsystem.h"
#include "Subsystem/TableSubsystem.h"
#include "DebugLog.h"
#include "Algo/BinarySearch.h"
#include "Math/UnrealMathUtility.h"
#include "../MannequinHunter.h"

const FName& FAIPatternStartData::GetPattern() const
{
	int32 rand = FMath::RandRange(0, maxWeight );
	int32 index = Algo::LowerBound(weights, rand);

	UE_LOG(LogTemp, Log, TEXT("Rand : %d, index : %d, weight : %d"), rand, index, weights[index]);
	return patternNames[index - 1];
}

void FAIPatternStartData::AddPattern(const FName& name, const int32 weight)
{
	AddWeightArray(weight);
	patternNames.Add(name);
}

void FAIPatternStartData::AddWeightArray(int32 weight)
{
	if (weight == 0)
		return;
	if (weights.Num() == 0)
		weights.Add(0);
	weights.Add(weight);
}

const TSharedPtr<FAIPatternTree>* UAIManagerSubsystem::GetPattern(const FName& tableName)
{
	const TSharedPtr<FAIPatternTree>* findPattern = AIPatternMap.Find(tableName);
	if (findPattern == nullptr)
		return LoadPattern(tableName);
	return findPattern;
}

void FAIPatternTree::SetupArrayData()
{
	if (indexArray.IsEmpty())
		return;
	fastArrayData = indexArray[0];
	lastArrayData = indexArray.Last();
}

const FPatternData* FAIPatternTree::GetPatternData(int32 distance)
{
	if (lastArrayData < distance)
		return nullptr;
	int32 index = Algo::UpperBound(indexArray, distance);

	if (currentIndex != index)
	{
		currentIndex = index;
		currentStartData = &patternTrees[index];
	}

	const FName& patternName = currentStartData->GetPattern();

	return patternDataMap.Find(patternName);
}

void FPatternData::SetPatternData(const FAIPatternDataTable& data)
{
	patternData = data;
	int32 total = 0;
	for (const FAIPatternData& data : patternData.addPatterns)
	{
		patternStartData.AddPattern(data.patternName, data.weight + total);
		total += data.weight;
	}
	patternStartData.SetMaxWeight(total);
}

const TSharedPtr<FAIPatternTree>* UAIManagerSubsystem::LoadPattern(const FName& tableRowName)
{
	UTableSubsystem* tableSubsystem = GetGameInstance()->GetSubsystem<UTableSubsystem>();

	const UDataTable* patternTreeTable = tableSubsystem->GetTable<FAIPatternTreeTable>();

	FAIPatternTreeTable* row = patternTreeTable->FindRow<FAIPatternTreeTable>(tableRowName, TEXT("Check AIPatternTreeTable"));
	if (row == nullptr)
		return nullptr;

	const UDataTable* patternTable = tableSubsystem->LoadAIPatternTable(row->patternDataTableName);

	if (patternTable == nullptr)
	{
		UE_LOG_WARNING(GameInstanceSubsystem, TEXT("%s Check Table"), *row->patternDataTableName.ToString());
		return nullptr;
	}

	 TSharedPtr<FAIPatternTree>& AIPatternTree = AIPatternMap.Add(row->patternDataTableName, MakeShared<FAIPatternTree>());

	 TArray<FAIPatternDataTable*> allDatas;
	 patternTable->GetAllRows(TEXT(""), allDatas);

	 for (const FAIPatternDataTable* tableData : allDatas)
	 {
		 //FPatternData& patternData = AIPatternTree->patternDataMap.Add(tableData->patternName, FPatternData());
		 FPatternData& patternData = AIPatternTree->AddPatternDataMap(tableData->patternName);
		 patternData.SetPatternData(*tableData);
	 }


	 row->patternData.KeySort([](const int32 a, const int32 b)
		{
			return a < b;
		});

	int32 index = 0;
	int32 total = 0;
	for (auto& patternDataPair : row->patternData)
	{
		int32 key = patternDataPair.Key;
		AIPatternTree->AddIndexArray(key * key);
		AIPatternTree->CreatePatternTree();
		//AIPatternTree->indexArray.Add(key * key);
		//AIPatternTree->patternTrees.Add(FAIPatternStartData());
		total = 0;
		FAIPatternStartData& patternDataMap = AIPatternTree->GetPatternTree(index);
		for (const FAIPatternTreeTableData& data : patternDataPair.Value.datas)
		{
			patternDataMap.AddPattern(data.data.patternName, data.data.weight + total);
			total += data.data.weight;
		}
		patternDataMap.SetMaxWeight(total);
		++index;
	}

	AIPatternTree->SetupArrayData();

	return &AIPatternTree;
}

