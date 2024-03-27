// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextProgressBarWidget.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;

UCLASS()
class MANNEQUINHUNTER_API UTextProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetProgressBar(int32 currentData, int32 maxData);
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY()
	TObjectPtr<UProgressBar> bar;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName progressBarName = TEXT("Bar");

	UPROPERTY()
	TObjectPtr <UTextBlock> text;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName textBlockName = TEXT("Text");
	
};
