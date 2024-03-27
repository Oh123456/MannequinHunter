// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainUIWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CombatSystem/Status.h"
#include "HUD/TextProgressBarWidget.h"

void UMainUIWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	playerHPBar = Cast<UTextProgressBarWidget>(GetWidgetFromName(TEXT("WBP_HP")));
	widgetMap.Add(EMainUIWidgetEnum::PlayerHPBar, playerHPBar);

	playerStaminaBar = Cast<UTextProgressBarWidget>(GetWidgetFromName(TEXT("WBP_Stamina")));
	widgetMap.Add(EMainUIWidgetEnum::PlayerStaminaBar, playerStaminaBar);

	bossHPBar = Cast<UTextProgressBarWidget>(GetWidgetFromName(TEXT("WBP_BossHP")));
	widgetMap.Add(EMainUIWidgetEnum::BossHPBar, bossHPBar);

	bossHPBar->SetVisibility(ESlateVisibility::Hidden);
}

void UMainUIWidget::SetWidgetVisibility(EMainUIWidgetEnum widgetEnum, ESlateVisibility visibillty)
{
	widgetMap[widgetEnum]->SetVisibility(visibillty);
}

void UMainUIWidget::SetHPBar(TObjectPtr<UTextProgressBarWidget> bar, const TSharedPtr<FStatusData>& status)
{
	bar->SetProgressBar(status->health, status->maxHealth);
}

void UMainUIWidget::SetStaminaBar(const TSharedPtr<FStatusData>& status)
{
	playerStaminaBar->SetProgressBar(status->stamina, status->maxStamina);
}

void UMainUIWidget::SetPlayerHPBar(const TSharedPtr<FStatusData>& status)
{
	SetHPBar(playerHPBar, status);
}

void UMainUIWidget::SetBossHPBar(const TSharedPtr<FStatusData>& status)
{
	SetHPBar(bossHPBar, status);
}
