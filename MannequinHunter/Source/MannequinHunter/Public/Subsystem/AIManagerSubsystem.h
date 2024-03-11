// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CombatSystem/CommandListTree.h"
#include "AI/AIPatternTable.h"
#include "AIManagerSubsystem.generated.h"

class MANNEQUINHUNTER_API FAIPatternStartData
{
public:
	void SetMaxWeight(int32 weight) { maxWeight = weight; }
	const int32 GetMaxWeight() const { return maxWeight; }

	const FName& GetPattern() const;

	void AddPattern(const FName& name, const int32 weight);
	void AddWeightArray(int32 weight);
private:
	TArray<int32> weights;
	TArray<FName> patternNames;

	int32 maxWeight;
};


// 가중치에 따라 나누기
class MANNEQUINHUNTER_API FPatternData
{
public:

	void SetPatternData(const FAIPatternDataTable& data);

	const FAIPatternDataTable& GetPatternData() const { return patternData; }
	const FAIPatternStartData& GetPatternStateData() const { return patternStartData; }

private:
	FAIPatternDataTable patternData;
	FAIPatternStartData patternStartData;
};

class MANNEQUINHUNTER_API FAIPatternTree
{
public:
	void SetupArrayData();

	const FPatternData* GetPatternData(int32 distance);
	const FAIPatternStartData* GetCurrentStartData() const { return currentStartData; }

	FPatternData& AddPatternDataMap(const FName& key) { return patternDataMap.Add(key, FPatternData()); }
	void AddIndexArray(const int32& index) { indexArray.Add(index); }
	int32 CreatePatternTree() { return patternTrees.Add(FAIPatternStartData()); }
	FAIPatternStartData& GetPatternTree(const int32 index) { return patternTrees[index]; }
	const FPatternData* GetPatternData(const FName& key) const { return patternDataMap.Find(key); }
private:
	// int32 거리 , 패턴 트리
	TArray<int32> indexArray;
	int32 fastArrayData;
	int32 lastArrayData;

	int32 currentIndex = -1;
	FAIPatternStartData* currentStartData = nullptr;

	TArray<FAIPatternStartData> patternTrees;

	TMap<FName, FPatternData> patternDataMap;
};


UCLASS()
class MANNEQUINHUNTER_API UAIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	const TSharedPtr<FAIPatternTree>* GetPattern(const FName& tableName);

private:
	const TSharedPtr<FAIPatternTree>* LoadPattern(const FName& tableRowName);

private:
	TMap<FName, TSharedPtr<FAIPatternTree>> AIPatternMap;
};
