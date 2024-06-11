// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterInformationWidget.generated.h"

/**
 * 
 */
struct FStatusData;

UCLASS()
class MANNEQUINHUNTER_API UCharacterInformationWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	void UpdateStatus(TArray<UWidget*>& textWidgets ,const TSharedPtr<FStatusData>& data);
	void ChangeStatus(const TSharedPtr<FStatusData>& data);
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	TObjectPtr<class UHorizontalBox> equipmentBox = nullptr;
	UPROPERTY()
	TObjectPtr<class UGridPanel> infoPanel = nullptr;

	FDelegateHandle changeStatusDelegateHandle;

	bool isChangeStatus = false;
};
