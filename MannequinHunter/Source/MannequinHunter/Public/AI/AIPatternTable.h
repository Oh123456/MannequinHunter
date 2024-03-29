// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CombatSystem/CombatAnimationEnums.h"
#include "AIPatternTable.generated.h"

/**
 * 
 */

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName patternName;

	UPROPERTY(EditDefaultsOnly)
	int32 weight;
};



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
	ECharacterCombatMontageType animSlot;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> montage;

	UPROPERTY(EditDefaultsOnly)
	FAIPatternCondition condition;

	UPROPERTY(EditDefaultsOnly)
	TArray<FAIPatternData> addPatterns;
};

USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FAIPatternTreeTableData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FAIPatternData data;
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

	virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
	{
		FAIPatternTreeTable* row = InDataTable->FindRow<FAIPatternTreeTable>(InRowName,TEXT(""));
		row->patternData.KeySort([](const int32& data1, const int32& data2)
			{
				return data1 < data2;
			});
	}
};

UCLASS()
class MANNEQUINHUNTER_API UAIPatternTable : public UDataTable
{
	GENERATED_BODY()
	
};
