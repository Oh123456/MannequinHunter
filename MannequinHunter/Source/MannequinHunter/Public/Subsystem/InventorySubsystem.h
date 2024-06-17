// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySubsystem.generated.h"

/**
 * 
 */

struct FItemData;

enum class EEquipment
{
	E_Weapone= 0,
	E_Armor,
	E_Accessories,
};

DECLARE_EVENT_TwoParams(UInventorySubsystem, FEquipmentEvent, EEquipment , const TSharedPtr<FItemData>);
DECLARE_EVENT_TwoParams(UInventorySubsystem, FAddInventoryEvent, const FName&, int32);

UCLASS()
class MANNEQUINHUNTER_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static const int MAX_ITEM_COUNT;

public:
	UInventorySubsystem();

	void Equipment(EEquipment slot, const TSharedPtr<FItemData>& data);
	void Equipment(EEquipment slot, int32 InventoryIndex);
	void RemoveEquipment(EEquipment slot);
	bool CheckEquipmentItem(EEquipment slot) { return (*equipment.Find(slot)) != nullptr; }
	void SetItemData(const int32 index, const TSharedPtr<FItemData>& data);
	void SetItemData(const int32 index, const FName& itemID);
	int32 FindEmptySlot();
	const TSharedPtr<FItemData>* GetItemData(const int32 index) const;
	const TArray<TSharedPtr<FItemData>>& GetItemDates() const { return items; }
	const TMap<EEquipment, TSharedPtr<FItemData>>& GetEquipment() const { return equipment; }

	void Reset();

	FEquipmentEvent& OnEquipment() { return equipmentEvent; }
	FAddInventoryEvent& OnAddInventoryEvent() { return addInventoryEvent; }
private:
	TArray<TSharedPtr<FItemData>> items;
	TMap<EEquipment, TSharedPtr<FItemData>> equipment;

	FEquipmentEvent equipmentEvent;
	FAddInventoryEvent addInventoryEvent;
};
