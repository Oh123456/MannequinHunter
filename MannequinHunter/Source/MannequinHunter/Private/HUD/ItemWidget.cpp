// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ItemWidget.h"
#include "Components/Image.h"

void UItemWidget::SetData(int32 id)
{
	itemId = id;
	// ���̺� �ε��ؼ� �̹��� �ֱ�

	
}

void UItemWidget::NativeOnInitialized()
{
	iconWidget = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
}
