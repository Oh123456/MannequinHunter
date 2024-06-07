// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CombatSystem/MannequinHunterStatus.h"
#include "InventorySubsystem.generated.h"

/**
 * 
 */

struct FItemData
{
public:
	FItemData(const FName& itemID, const struct FItemTable* tableData);
	FItemData() : id(), statusData() {};
public:
	FName id;
	FMannequinHunterStatusData statusData;
};


UCLASS()
class MANNEQUINHUNTER_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static const int MAX_ITEM_COUNT;

public:
	UInventorySubsystem();

	void SetItemData(const int32 index, const FItemData& data);
	void SetItemData(const int32 index, const FName& itemID);
	const FItemData* GetItemData(const int32 index) const;
	const TArray<FItemData>& GetItemDates() const { return items; }

	void Reset();
private:
	TArray<FItemData> items;
};
