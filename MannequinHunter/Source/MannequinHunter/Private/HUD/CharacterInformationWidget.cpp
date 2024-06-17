// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/CharacterInformationWidget.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MannequinHunterPlayerCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "CombatSystem/Status.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Subsystem/InventorySubsystem.h"
#include "HUD/ItemWidget.h"
#include "Item/Item.h"
#include "Internationalization/StringTableRegistry.h"
#include "Subsystem/TableSubsystem.h"

#define SET_STATUS_TEXT_DATA(widget, argData, keyText) \
{\
	UTextBlock* textBlock = Cast<UTextBlock>(widget);\
	FText text = FText::Format(FText::FromStringTable(UTableSubsystem::STRINGTABLE_UI_PATH, TEXT(keyText)), FText::AsNumber(argData));\
	textBlock->SetText(text);\
}\

int32 testValue = 123456789;

void UCharacterInformationWidget::UpdateStatus(const TSharedPtr<FStatusData>& data)
{
	int32 count = 0;

	TArray<UWidget*> textWidgets = infoPanel->GetAllChildren();


	SET_STATUS_TEXT_DATA(textWidgets[count++], data->maxHealth, "Text_MaxHealth");
	SET_STATUS_TEXT_DATA(textWidgets[count++], data->maxStamina, "Text_MaxStamina");
	SET_STATUS_TEXT_DATA(textWidgets[count++], data->attack, "Text_Attack");
	SET_STATUS_TEXT_DATA(textWidgets[count++], data->attackSpeed, "Text_AttackSpeed");
	SET_STATUS_TEXT_DATA(textWidgets[count++], data->defensive, "Text_Defensive");



}

void UCharacterInformationWidget::ChangeStatus(const TSharedPtr<FStatusData>& data)
{
	if (IsInViewport())
	{
		UpdateStatus(data);
	}
	else
	{
		EnumAddFlags<EChangeInformationData>(changeData, EChangeInformationData::E_Status);
	}
}

void UCharacterInformationWidget::UpdateEquipment()
{
	UInventorySubsystem* inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();


	const auto& equipmentMap = inventory->GetEquipment();
	for (const auto& pair : equipmentMap)
	{

		UItemWidget* widget = Cast<UItemWidget>(equipmentBox->GetChildAt(StaticCast<int32>(pair.Key)));
		if (pair.Value == nullptr)
		{
			widget->Clear();
			continue;
		}

		widget->SetData((pair.Value)->id);
	}
}

void UCharacterInformationWidget::ChangeEquipment(EEquipment slot, const TSharedPtr<FItemData> data)
{
	if (IsInViewport())
	{

		UItemWidget* itemWidget = Cast<UItemWidget>(equipmentBox->GetChildAt(StaticCast<int32>(slot)));
		if (data == nullptr)
			itemWidget->Clear();
		else
			itemWidget->SetData(data->id);
	}
	else
	{
		EnumAddFlags<EChangeInformationData>(changeData, EChangeInformationData::E_Equipment);
	}
}

void UCharacterInformationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	equipmentBox = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("ItemHorizontalBox")));
	infoPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("InfoPanel")));

	AMannequinHunterPlayerCharacter* player = Cast<AMannequinHunterPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player == nullptr)
		return;
	FStatus& status = player->GetCombatComponent()->GetStatusData();
	TArray<UWidget*> children = equipmentBox->GetAllChildren();

	for (int32 i = 0; i < children.Num(); i++)
	{
		Cast<UItemWidget>(children[i])->SetIndex(i);
	}

	UpdateStatus(status.GetStatusData());
	UpdateEquipment();

}

void UCharacterInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMannequinHunterPlayerCharacter* player = Cast<AMannequinHunterPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player == nullptr)
		return;
	FStatus& status = player->GetCombatComponent()->GetStatusData();
	/*changeStatusDelegateHandle = */status.OnChangeStatus.AddUObject(this, &UCharacterInformationWidget::ChangeStatus);

	if (EnumHasAnyFlags(changeData, EChangeInformationData::E_Status))
	{

		UpdateStatus(status.GetStatusData());
		EnumRemoveFlags(changeData, EChangeInformationData::E_Status);
	}

	UInventorySubsystem* inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	/*changeEquipmentDelegateHandle = */inventory->OnEquipment().AddUObject(this, &UCharacterInformationWidget::ChangeEquipment);

	if (EnumHasAnyFlags(changeData, EChangeInformationData::E_Equipment))
	{
		UpdateEquipment();
		EnumRemoveFlags(changeData, EChangeInformationData::E_Equipment);
	}
}

void UCharacterInformationWidget::NativeDestruct()
{
	Super::NativeDestruct();

	//AMannequinHunterPlayerCharacter* player = Cast<AMannequinHunterPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//if (player == nullptr)
	//	return;
	//FStatus& status = player->GetCombatComponent()->GetStatusData();
	//status.OnChangeStatus.Remove(changeStatusDelegateHandle);

	//UInventorySubsystem* inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	//inventory->OnEquipment().Remove(changeEquipmentDelegateHandle);
}
