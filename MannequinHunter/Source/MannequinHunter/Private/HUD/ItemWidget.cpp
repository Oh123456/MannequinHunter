// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ItemWidget.h"
#include "Components/Image.h"
#include "Subsystem/TableSubsystem.h"
#include "Subsystem/InventorySubsystem.h"
#include "Table/ItemDataTable.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Input/Events.h"

void UItemWidget::SetData(const FName& id)
{
	ItemID = const_cast<FName*>(&id);
	UGameInstance* gameInstance = GetGameInstance();
	UTableSubsystem* tableSubsystem = gameInstance->GetSubsystem<UTableSubsystem>();

	FItemDataTableResult result;
	tableSubsystem->GetItemTable(id , result);
	const UDataTable* itemTable = result.table;
	itemData = itemTable->FindRow<FItemTable>(id,TEXT(""));

	if (itemData == nullptr)
	{
		Clear();
		return;
	}

	iconWidget->SetBrushFromTexture(itemData->icon);
	iconWidget->SetColorAndOpacity(FLinearColor::White);
}

void UItemWidget::Clear()
{
	ItemID = nullptr;
	itemData = nullptr;
	iconWidget->SetBrushFromTexture(nullptr);
	FLinearColor color = FLinearColor::White;
	color.A = 0.0f;
	iconWidget->SetColorAndOpacity(color);
}

void UItemWidget::NativeOnInitialized()
{
	iconWidget = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	Clear();
}



void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}
