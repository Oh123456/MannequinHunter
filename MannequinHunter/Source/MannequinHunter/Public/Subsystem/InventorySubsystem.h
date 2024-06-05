// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySubsystem.generated.h"

/**
 * 
 */

struct FITemData
{
	int32 id = -1;

};


UCLASS()
class MANNEQUINHUNTER_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static const int MAX_ITEM_COUNT;

public:
	UInventorySubsystem();

	void SetItemData(const int32 index, const FITemData& data);
	const FITemData* GetItemData(const int32 index) const;

	void Reset();
private:
	TArray<FITemData> items;
};
