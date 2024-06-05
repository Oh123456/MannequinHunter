// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventoryWidget.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "HUD/ItemWidget.h"
#include "Subsystem/InventorySubsystem.h"



UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//ConstructorHelpers::FObjectFinder<UItemWidget> Item_Widget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP/HUD/WBP_Item.WBP_Item'"));
	//if (Item_Widget.Succeeded())
	//{
	//	itemWidget = Item_Widget.Object;
	//}
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

		UUserWidget* widget = CreateWidget(GetWorld(), itemWidget);

		UGridSlot* slot = gridPanel->AddChildToGrid(widget, i / column, i % column);
		slot->Nudge.X = 10.f;
	}

}
