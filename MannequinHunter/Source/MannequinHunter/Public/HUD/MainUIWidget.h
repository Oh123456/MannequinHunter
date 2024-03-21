// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	TObjectPtr< class UProgressBar> hpBar;
	
	UPROPERTY()
	TObjectPtr < class UTextBlock> hpText;

	UPROPERTY()
	TObjectPtr< class UProgressBar> staminaBar;

	UPROPERTY()
	TObjectPtr < class UTextBlock> staminaText;

};
