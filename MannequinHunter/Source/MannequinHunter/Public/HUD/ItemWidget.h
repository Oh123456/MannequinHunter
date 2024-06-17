// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */

struct FItemTable;

UCLASS()
class MANNEQUINHUNTER_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetIndex(int32 num) { this->index = num; }
	void SetData(const FName& id);
	const FItemTable* GetItemData() const { return itemData; }
	void Clear();
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
protected:
	UPROPERTY()
	TObjectPtr<class UImage> iconWidget;

	FName* ItemID;

	const FItemTable* itemData;
	int32 index = 0;
};
