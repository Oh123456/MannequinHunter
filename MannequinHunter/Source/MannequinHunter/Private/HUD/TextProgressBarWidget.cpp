// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TextProgressBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UTextProgressBarWidget::SetProgressBar(int32 currentData, int32 maxData)
{
	text->SetText(FText::AsNumber(currentData));


	float percent = StaticCast<float>(StaticCast<float>(currentData) / StaticCast<float>(maxData));


	bar->SetPercent(percent);
}

void UTextProgressBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	bar = Cast<UProgressBar>(GetWidgetFromName(progressBarName));
	text = Cast<UTextBlock>(GetWidgetFromName(textBlockName));
}
