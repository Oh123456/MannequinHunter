// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Defines.h"
#include "CombatSystem/CommandListTree.h"
#include "AI/AIPatternTable.h"
#include "AIPattern.generated.h"

// 가중치에 따라 나누기
class FAICommandTreeData
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


UCLASS(Blueprintable)
class MANNEQUINHUNTER_API UAIPattern : public UObject
{
	GENERATED_BODY()
public:
	~UAIPattern();

	void LoadTableData(UWorld* world);

	int32 GetDefaultWeight() const { return defaultWeight; }
	const FAIPatternTreeTableDataArray* GetAIPatternData(float distance) const;

private:
	const FAIPatternTreeTable* tableData;
	int32 defaultWeight = 100;

private:
	UPROPERTY(EditDefaultsOnly, Category = Table, meta = (ALLOW_PRIVATE_ACCESS))
	FName tableName;

};
