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
	UTableSubsystem* tableSubsystem = GetGameInstance()->GetSubsystem<UTableSubsystem>();

	const UDataTable* itemTable = tableSubsystem->GetTable<FItemTable>();
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

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		UInventorySubsystem* inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
		inventory->Equipment(EEquipment::E_Weapone, index);
		const FName& id = inventory->GetItemData(index)->id;
		if (id.IsNone())
			Clear();
		else
			SetData(id);
		UE_LOG(LogTemp,Log,TEXT("MouseButtonDown !! "));
	}
	return reply;
}
