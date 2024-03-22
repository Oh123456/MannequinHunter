// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainUIWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CombatSystem/Status.h"

void UMainUIWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	hpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	hpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HP_Text")));

	staminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Stamina_Bar")));
	staminaText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Stamina_Text")));
}

void UMainUIWidget::SetHP(const TSharedPtr<FStatusData>& status)
{
	SetProgressBar(hpBar, hpText, status->health, status->maxHealth);
}

void UMainUIWidget::SetStamina(const TSharedPtr<FStatusData>& status)
{
	SetProgressBar(staminaBar, staminaText, status->stamina, status->maxStamina);
}

void UMainUIWidget::SetProgressBar(UProgressBar* bar, UTextBlock* text, int32 currentData, int32 maxData)
{
	text->SetText(FText::AsNumber(currentData));


	float percent = StaticCast<float>(StaticCast<float>(currentData) / StaticCast<float>(maxData));


	bar->SetPercent(percent);	
}
