// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY()
	TObjectPtr<class UGridPanel> gridPanel;

	//UPROPERTY()
	//TObjectPtr<class UItemWidget> itemWidget;
};
