// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventoryItemWidget.h"
#include "Subsystem/InventorySubsystem.h"
#include "Table/ItemDataTable.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Input/Events.h"

FReply UInventoryItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		UInventorySubsystem* inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
		const TSharedPtr<FItemData>* item = inventory->GetItemData(index);
		if (*item != nullptr && ((*item)->type == EItemType::E_Weapon ||
			(*item)->type == EItemType::E_Equipment))
		{

			inventory->Equipment(EEquipment::E_Weapone, index);
			const TSharedPtr<FItemData>* data = inventory->GetItemData(index);
			if ((*data) == nullptr)
				Clear();
			else
				SetData((*data)->id);

		}
		//UE_LOG(LogTemp, Log, TEXT("MouseButtonDown !! "));
	}
	return reply;
}

const TSharedPtr<FItemData>* UInventoryItemWidget::GetItemData()
{
	if (IsEmpty())
		return nullptr;

	UInventorySubsystem* inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	return inventory->GetItemData(index);
}
