// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AIPatternTable.generated.h"

/**
 * 
 */
USTRUCT(Blueprinttype)
struct FAIPatternCondition
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float distance;

};

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName patternName;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> montage;

	UPROPERTY(EditDefaultsOnly)
	FAIPatternCondition condition;
};

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternTreeData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName patternName;

	UPROPERTY(EditDefaultsOnly)
	int32 weight;
};


USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternTreeTableData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FAIPatternTreeData data;

	UPROPERTY(EditDefaultsOnly)
	TArray<FAIPatternTreeData> addPattern;
};


USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternTreeTableDataArray
{
	GENERATED_BODY()



	UPROPERTY(EditDefaultsOnly)
	TArray<FAIPatternTreeTableData> datas;

};

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternTreeTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName patternDataTableName;

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, FAIPatternTreeTableDataArray> patternData;

};

UCLASS()
class MANNEQUINHUNTER_API UAIPatternTable : public UDataTable
{
	GENERATED_BODY()
	
};
