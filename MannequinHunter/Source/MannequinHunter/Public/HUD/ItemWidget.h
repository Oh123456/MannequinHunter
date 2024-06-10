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
	void SetData(const FName& id);
	const FItemTable* GetItemData() const { return itemData; }
	void Clear();
protected:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
private:
	UPROPERTY()
	TObjectPtr<class UImage> iconWidget;

	const FItemTable* itemData;

};
