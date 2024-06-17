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

	void Refresh();
private:
	void Refresh(const FName& id, int32 index);
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	TObjectPtr<class UGridPanel> gridPanel;
};
