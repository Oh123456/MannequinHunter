// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/ItemWidget.h"
#include "InventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UInventoryItemWidget : public UItemWidget
{
	GENERATED_BODY()

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
