// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Defines.h"
#include "AIPattern.generated.h"

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> montage;
};

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, FAIPatternData> patternData;

};



UCLASS(Blueprintable)
class MANNEQUINHUNTER_API UAIPattern : public UObject
{
	GENERATED_BODY()
public:
	~UAIPattern();

	void LoadTableData();

	const FAIPatternData* GetAIPatternData(FString patternKey) const;

private:
	const FAIPatternTable* tableData;
private:
	UPROPERTY(EditDefaultsOnly, Category = Table, meta = (ALLOW_PRIVATE_ACCESS))
	FName tableName;
};
