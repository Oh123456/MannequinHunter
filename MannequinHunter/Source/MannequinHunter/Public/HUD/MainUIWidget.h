// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;
struct FStatusData;

UCLASS()
class MANNEQUINHUNTER_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

public:
	void SetHP(const TSharedPtr<FStatusData>& status);
	void SetStamina(const TSharedPtr<FStatusData>& status);

private:
	void SetProgressBar(UProgressBar* bar, UTextBlock* text, int32 currentData, int32 maxData);
private:
	UPROPERTY()
	TObjectPtr<UProgressBar> hpBar;
	
	UPROPERTY()
	TObjectPtr <UTextBlock> hpText;

	UPROPERTY()
	TObjectPtr<UProgressBar> staminaBar;

	UPROPERTY()
	TObjectPtr <UTextBlock> staminaText;

};
