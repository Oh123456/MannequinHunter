// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Containers/List.h"
#include "UISubsystem.generated.h"

/**
 * 
 */

DECLARE_EVENT_OneParam(UUISubsystem,FActiveEvent,UUserWidget*);

UCLASS()
class MANNEQUINHUNTER_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Show widgetClass
	void Show(UClass* widgetClass, int32 ZOrder = 0);

	// Hide Last Widget
	void Hide();

	// Hide Show widgetClass
	void Hide(UClass* widgetClass);

	int32 Count() { return activeUIList.Num(); }
	bool IsShow(UClass* widgetClass);

	FActiveEvent& OnShow() { return showEvent; }
	FActiveEvent& OnHide() { return hideEvent; }
private:
	TDoubleLinkedList<TObjectPtr<UUserWidget>>::TDoubleLinkedListNode* CheckActiveList(TObjectPtr<UUserWidget>* ui);
private:
	TDoubleLinkedList<TObjectPtr<UUserWidget>> activeUIList;

	TMap<TObjectPtr<UClass>, TObjectPtr<UUserWidget>> cachedUI;

	FActiveEvent showEvent;
	FActiveEvent hideEvent;
};
