// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ItemWidget.h"
#include "Components/Image.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/ItemDataTable.h"

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
