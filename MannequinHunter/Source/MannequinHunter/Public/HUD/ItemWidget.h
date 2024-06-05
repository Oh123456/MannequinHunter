// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetData(int32 id);

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	TObjectPtr<class UImage> iconWidget;

	int32 itemId = -1;
};
