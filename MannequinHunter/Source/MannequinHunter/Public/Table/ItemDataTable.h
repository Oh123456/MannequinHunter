// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Combatsystem/MannequinHunterStatus.h"
#include "ItemDataTable.generated.h"

/**
 * 
 */

USTRUCT(Blueprinttype)
struct FItemTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FName itemName;
	UPROPERTY(EditDefaultsOnly)
	FName itemDes;
	UPROPERTY(EditDefaultsOnly)
	FMannequinHunterStatusData statusData;
	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* icon;
};

UCLASS()
class MANNEQUINHUNTER_API UItemDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
