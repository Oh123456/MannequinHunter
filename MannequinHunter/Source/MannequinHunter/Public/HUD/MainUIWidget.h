// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.generated.h"

/**
 * 
 */

class UTextProgressBarWidget;
struct FStatusData;

UENUM()
enum class EMainUIWidgetEnum : uint8
{
	PlayerHPBar = 0,
	PlayerStaminaBar,
	BossHPBar,
};

UCLASS()
class MANNEQUINHUNTER_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

public:
	void SetWidgetVisibility(EMainUIWidgetEnum widgetEnum, ESlateVisibility visibillty);

	void SetStaminaBar(const TSharedPtr<FStatusData>& status);

	void SetPlayerHPBar(const TSharedPtr<FStatusData>& status);
	void SetBossHPBar(const TSharedPtr<FStatusData>& status);
private:
	void SetHPBar(TObjectPtr<UTextProgressBarWidget> bar ,const TSharedPtr<FStatusData>& status);

private:

	UPROPERTY()
	TMap<EMainUIWidgetEnum, TObjectPtr<UWidget>> widgetMap;

	// 자주 호출하는것은 캐스팅 비용 아끼기위해 따로 저장함
	UPROPERTY()
	TObjectPtr<UTextProgressBarWidget> playerHPBar;
	// 자주 호출하는것은 캐스팅 비용 아끼기위해 따로 저장함
	UPROPERTY()
	TObjectPtr<UTextProgressBarWidget> playerStaminaBar;
	// 자주 호출하는것은 캐스팅 비용 아끼기위해 따로 저장함
	UPROPERTY()
	TObjectPtr<UTextProgressBarWidget> bossHPBar;


};
