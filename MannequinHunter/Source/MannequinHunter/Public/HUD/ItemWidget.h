// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */

struct FItemTable;
struct FItemData;

UCLASS()
class MANNEQUINHUNTER_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetIndex(int32 num) { this->index = num; }
	void SetData(const FName& id);
	const FItemTable* GetItemTableData() const { return itemData; }
	void Clear();

	bool IsEmpty() { return (ItemID == nullptr || ItemID->IsNone()); }
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual const TSharedPtr<FItemData>* GetItemData();
protected:
	UPROPERTY()
	TObjectPtr<class UImage> iconWidget;

	FName* ItemID;

	const FItemTable* itemData;
	int32 index = 0;

private:
	UPROPERTY()
	class UItemInformationWidget* activeInfoWidget = nullptr;

	FTimerHandle infoTimerHandle;

	FVector2D infoWidgetOffset { 10.0f,10.0f };
};
