// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Defines.h"
#include "AIPattern.generated.h"

USTRUCT(Blueprinttype)
struct FAIPatternCondition
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float distance;

};

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName patternName;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> montage;

	UPROPERTY(EditDefaultsOnly)
	int32 weight;

	UPROPERTY(EditDefaultsOnly)
	FAIPatternCondition condition;
};

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternDataArray
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FAIPatternData> datas;
};

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, FAIPatternDataArray> patternData;

};



UCLASS(Blueprintable)
class MANNEQUINHUNTER_API UAIPattern : public UObject
{
	GENERATED_BODY()
public:
	~UAIPattern();

	void LoadTableData(UWorld* world);

	int32 GetDefaultWeight() const { return defaultWeight; }
	const FAIPatternDataArray* GetAIPatternData(float distance) const;
private:
	const FAIPatternTable* tableData;
	int32 defaultWeight = 300;
private:
	UPROPERTY(EditDefaultsOnly, Category = Table, meta = (ALLOW_PRIVATE_ACCESS))
	FName tableName;

};
