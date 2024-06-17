// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Combatsystem/MannequinHunterStatus.h"
#include "Item/Item.h"
#include "ItemDataTable.generated.h"

/**
 * 
 */

USTRUCT(Blueprinttype)
struct FItemKeyTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FString itemKey;
	UPROPERTY(EditDefaultsOnly)
	EItemType itemType;
};

USTRUCT(Blueprinttype)
struct FItemTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	EItemType itemType;
	UPROPERTY(EditDefaultsOnly)
	FName itemName;
	UPROPERTY(EditDefaultsOnly)
	FName itemDes;
	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* icon;
};

USTRUCT(Blueprinttype)
struct FEquipmentItemTable : public FItemTable
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	float weaponConstant;
	UPROPERTY(EditDefaultsOnly)
	FMannequinHunterStatusData statusData;
};

UCLASS()
class MANNEQUINHUNTER_API UItemDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
