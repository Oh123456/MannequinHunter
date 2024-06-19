// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ItemInformationWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Item/Item.h"
#include "Table/ItemDataTable.h"
#include "Defines.h"
#include "Subsystem/TableSubsystem.h"


#define PUSH_ITEM_DATA(tarray ,stringKey, itemValue) \
if (itemValue != 0)\
	tarray.Add(FItemInfoData{ TEXT(stringKey), itemValue });\

void UItemInformationWidget::SetData(const TSharedPtr<FItemData>& data)
{
	//TODO::
	TArray<UWidget*> textWidgets = infoPanel->GetAllChildren();
	SetItemData(data);
	int i = 0;
	for (const FItemInfoData& infoData : itemDates)
	{
		UWidget* widget = textWidgets[i++];
		TEXTBLOCK_FORMAT_ONEPARAM(UTableSubsystem::STRINGTABLE_UI_PATH, widget, infoData.value, *infoData.stringTableKey);
		widget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	FItemDataTableResult result;
	GetGameInstance()->GetSubsystem<UTableSubsystem>()->GetItemTable(data->id, result);
	const FItemTable* tableData = result.table->FindRow<FItemTable>(data->id,TEXT(""));

	iconWidget->SetBrushFromTexture(tableData->icon);

	itemName->SetText(FText::FromStringTable(UTableSubsystem::STRINGTABLE_ITEM_PATH, tableData->itemName.ToString()));
	itemDes->SetText(FText::FromStringTable(UTableSubsystem::STRINGTABLE_ITEM_PATH, tableData->itemDes.ToString()));
}

void UItemInformationWidget::Clear()
{
	TArray<UWidget*> children = infoPanel->GetAllChildren();

	for (UWidget* widget : children)
		widget->SetVisibility(ESlateVisibility::Hidden);
}

void UItemInformationWidget::ReSize()
{
	sizeBox->SetWidthOverride(defaultSize.X);
	sizeBox->SetHeightOverride(defaultSize.Y);

	//위젯 구성 후 1-2프레임 후에만 작동합니다.???
	SetDesiredSizeInViewport(defaultSize);
}

void UItemInformationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	iconWidget = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	itemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	itemDes = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDes")));
	infoPanel = Cast<UVerticalBox>(GetWidgetFromName(TEXT("InfoPanel")));

	sizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("SizePanel")));
	ReSize();
	Clear();

}

void UItemInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReSize();
	Clear();
}

void UItemInformationWidget::SetItemData(const TSharedPtr<FItemData>& data)
{
	itemDates.Reset(0);

	const FMannequinHunterStatusData statusData = data->GetStatusData();

	PUSH_ITEM_DATA(itemDates, "Text_MaxHealth", statusData.maxHealth);
	PUSH_ITEM_DATA(itemDates, "Text_MaxStamina", statusData.maxStamina);
	PUSH_ITEM_DATA(itemDates, "Text_Attack", statusData.attack);
	PUSH_ITEM_DATA(itemDates, "Text_AttackSpeed", statusData.attackSpeed);
	PUSH_ITEM_DATA(itemDates, "Text_Defensive", statusData.defensive);

}
