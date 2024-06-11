// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventoryWidget.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "HUD/ItemWidget.h"
#include "Subsystem/InventorySubsystem.h"



UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UInventoryWidget::Refresh()
{
	UInventorySubsystem* inventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	const TArray<FItemData>& items = inventorySubsystem->GetItemDates();
	for (int i = 0; i < UInventorySubsystem::MAX_ITEM_COUNT; i++)
	{
		if (items[i].id.IsNone())
			continue;

		UItemWidget* itemWidget = Cast<UItemWidget>(gridPanel->GetChildAt(i));
		itemWidget->SetData(items[i].id);
	}
}

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	gridPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("ItemGridPanel")));

	TSubclassOf<UItemWidget> itemWidget = LoadClass<UItemWidget>(nullptr, TEXT("/Game/BP/HUD/WBP_Item.WBP_Item_C"));

	if (itemWidget == nullptr)
		return;

	const int column = 7;
	for (int i = 0; i < UInventorySubsystem::MAX_ITEM_COUNT; i++)
	{

		UItemWidget* widget = CreateWidget<UItemWidget>(GetWorld(), itemWidget);
		widget->SetIndex(i);
		UGridSlot* slot = gridPanel->AddChildToGrid(widget, i / column, i % column);
		slot->Nudge.X = 10.f;
	}

}

void UInventoryWidget::NativeConstruct()
{
	Refresh();
}
