// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainUIWidget.h"
#include "Components/ProgressBar.h"

void UMainUIWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	hpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	if (hpBar)
	{
		hpBar->Percent = 1.0f;
	}
}
