// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Defines.h"
#include "CombatSystem/CommandListTree.h"
#include "AI/AIPatternTable.h"
#include "AIPattern.generated.h"

class FAIPatternTree;

UCLASS(Blueprintable)
class MANNEQUINHUNTER_API UAIPattern : public UObject
{
	GENERATED_BODY()
public:
	~UAIPattern();

	void LoadTableData(UWorld* world);

private:
	TSharedPtr<FAIPatternTree> pattern;
private:
	UPROPERTY(EditDefaultsOnly, Category = Table, meta = (ALLOW_PRIVATE_ACCESS))
	FName tableName;

};
