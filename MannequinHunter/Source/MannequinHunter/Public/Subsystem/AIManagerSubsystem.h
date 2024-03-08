// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CombatSystem/CommandListTree.h"
#include "AI/AIPatternTable.h"
#include "AIManagerSubsystem.generated.h"

class FAIPatternStartData
{
public:
	void SetMaxWeight(int32 weight) { maxWeight = weight; }
	const int32 GetMaxWeight() const { return maxWeight; }

	void AddPattern(const FName& name, const int32 weight);
	void AddWeightArray(int32 weight);
private:
	TArray<int32> weights;
	TArray<FName> patternNames;

	int32 maxWeight;
};


// 가중치에 따라 나누기
class FPatternData
{
public:

	void SetPatternData(const FAIPatternDataTable& data);

	const FAIPatternDataTable& GetPatternData() const { return patternData; }
	const FAIPatternStartData& GetPatternStateData() const { return patternStartData; }

private:
	FAIPatternDataTable patternData;
	FAIPatternStartData patternStartData;
};

class FAIPatternTree
{
public:

public:
	// int32 거리 , 패턴 트리
	TArray<int32> indexArray;

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
