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

	// ���� ȣ���ϴ°��� ĳ���� ��� �Ƴ������� ���� ������
	UPROPERTY()
	TObjectPtr<UTextProgressBarWidget> playerHPBar;
	// ���� ȣ���ϴ°��� ĳ���� ��� �Ƴ������� ���� ������
	UPROPERTY()
	TObjectPtr<UTextProgressBarWidget> playerStaminaBar;
	// ���� ȣ���ϴ°��� ĳ���� ��� �Ƴ������� ���� ������
	UPROPERTY()
	TObjectPtr<UTextProgressBarWidget> bossHPBar;


};
