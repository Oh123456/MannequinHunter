// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UItemInformationWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	struct FItemInfoData
	{
		FItemInfoData(TCHAR* key, int32 stateData) : stringTableKey(key), value(stateData) {}
		const FString stringTableKey;
		const int32 value;
	};
public:
	void SetData(const TSharedPtr<struct FItemData>& data );
	void Clear();
	void ReSize();
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	void SetItemData(const TSharedPtr<FItemData>& data);
private:
	UPROPERTY()
	TObjectPtr<class USizeBox> sizeBox;

	UPROPERTY()
	TObjectPtr<class UImage> iconWidget;
	
	UPROPERTY()

	TObjectPtr<class UTextBlock> itemName;

	UPROPERTY()

	TObjectPtr<class UTextBlock> itemDes;

	UPROPERTY()
	TObjectPtr<class UVerticalBox> infoPanel;

	const FVector2D defaultSize { 300.0f ,500.0f };

	TArray<FItemInfoData> itemDates;
};
