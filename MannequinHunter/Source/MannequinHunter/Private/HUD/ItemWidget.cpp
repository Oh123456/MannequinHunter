// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ItemWidget.h"
#include "Components/Image.h"

void UItemWidget::SetData(int32 id)
{
	itemId = id;
	// 테이블 로드해서 이미지 넣기

	
}

void UItemWidget::NativeOnInitialized()
{
	iconWidget = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
}
