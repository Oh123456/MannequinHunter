// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Container/Tree.h"
#include "AI/AIPatternTable.h"
#include "AIManagerSubsystem.generated.h"


// 가중치에 따라 나누기
class FPatternData
{
public:

	void SetPatternData(const FAIPatternDataTable& data, int32 weightValue) { patternData = data; this->weight = weightValue; }

	const FAIPatternDataTable& GetPatternData() const { return patternData; }
	const int32 GetWeight() const { return weight; }

	void AddWeightArray(int32 weight);

private:
	FAIPatternDataTable patternData;
	int32 weight;
	TArray<int32> weightArray;
};

struct FAIPatternTree
{
	// int32 거리 , 패턴 트리
	TMap<int32, TTree<FName, FPatternData>> patternTrees;
};


UCLASS()
class MANNEQUINHUNTER_API UAIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	const TSharedPtr<FAIPatternTree> GetPattern(const FName& tableName) const;

private:
	void LoadPattern(const FName& tableRowName);

private:
	TMap<FName, TSharedPtr<FAIPatternTree>> AIPatternMap;
};
