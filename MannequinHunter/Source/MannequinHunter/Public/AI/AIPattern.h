// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Defines.h"
#include "AIPattern.generated.h"

struct FAIPatternTreeTableDataArray;
struct FAIPatternTreeTable;

// 가중치에 따라 나누기
struct FAICommandTreeData
{

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
	int32 defaultWeight = 300;
private:
	UPROPERTY(EditDefaultsOnly, Category = Table, meta = (ALLOW_PRIVATE_ACCESS))
	FName tableName;

};
