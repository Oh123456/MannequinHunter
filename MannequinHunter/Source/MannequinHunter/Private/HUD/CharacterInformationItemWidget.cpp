// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/CharacterInformationItemWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Subsystem/InventorySubsystem.h"
#include "Input/Events.h"
#include "Item/Item.h"
#include "Table/ItemDataTable.h"

FReply UCharacterInformationItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply replay =  Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		UInventorySubsystem* inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
		if (!inventory->CheckEquipmentItem(StaticCast<EEquipment>(index)))
			return replay;
		int32 InventoryIndex = inventory->FindEmptySlot();
		if (InventoryIndex == -1)
			return replay;

		inventory->RemoveEquipment(EEquipment::E_Weapone);
		inventory->SetItemData(InventoryIndex, *ItemID);
		Clear();
	}

	return replay;
}

const TSharedPtr<FItemData>* UCharacterInformationItemWidget::GetItemData()
{
	if (IsEmpty())
		return nullptr;

	UInventorySubsystem* inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();

	return &inventory->GetEquipment()[StaticCast<EEquipment>(index)];
}
