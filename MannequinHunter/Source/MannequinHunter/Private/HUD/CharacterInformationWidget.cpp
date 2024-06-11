// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/CharacterInformationWidget.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MannequinHunterPlayerCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "CombatSystem/Status.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"

#define SET_STATUS_TEXT_DATA(widget, argData) \
{\
	UTextBlock* textBlock = Cast<UTextBlock>(widget); \
	FText text = textBlock->GetText(); \
	FStringFormatArg args(argData); \
	FStringFormatOrderedArguments orderedArg; \
	orderedArg.Add(args); \
	textBlock->SetText(FText::FromString(FString::Format(*text.ToString(), orderedArg))); \
} \

void UCharacterInformationWidget::UpdateStatus(TArray<UWidget*>& textWidgets, const TSharedPtr<FStatusData>& data)
{
	int32 count = 0;

	SET_STATUS_TEXT_DATA(textWidgets[count++], data->maxHealth);
	SET_STATUS_TEXT_DATA(textWidgets[count++], data->maxStamina);
	SET_STATUS_TEXT_DATA(textWidgets[count++], data->attack);
	SET_STATUS_TEXT_DATA(textWidgets[count++], data->attackSpeed);
	SET_STATUS_TEXT_DATA(textWidgets[count++], data->defensive);

}

void UCharacterInformationWidget::ChangeStatus(const TSharedPtr<FStatusData>& data)
{
	if (IsInViewport())
	{
		TArray<UWidget*> children = infoPanel->GetAllChildren();
		UpdateStatus(children, data);
	}
	else
	{
		isChangeStatus = true;
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
	TArray<UWidget*> children = infoPanel->GetAllChildren();

	UpdateStatus(children, status.GetStatusData());
}

void UCharacterInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMannequinHunterPlayerCharacter* player = Cast<AMannequinHunterPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player == nullptr)
		return;
	FStatus& status = player->GetCombatComponent()->GetStatusData();
	changeStatusDelegateHandle = status.OnChangeStatus.AddUObject(this, &UCharacterInformationWidget::ChangeStatus);

	if (isChangeStatus)
	{
		TArray<UWidget*> children = infoPanel->GetAllChildren();

		UpdateStatus(children, status.GetStatusData());

		isChangeStatus = false;
	}
}

void UCharacterInformationWidget::NativeDestruct()
{
	Super::NativeDestruct();

	AMannequinHunterPlayerCharacter* player = Cast<AMannequinHunterPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player == nullptr)
		return;
	FStatus& status = player->GetCombatComponent()->GetStatusData();
	status.OnChangeStatus.Remove(changeStatusDelegateHandle);
}
