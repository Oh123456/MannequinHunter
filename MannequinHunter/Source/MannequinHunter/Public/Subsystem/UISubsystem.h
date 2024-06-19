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
	UUISubsystem();

	// Show From Name
	template<typename T>
	T* Show(const TCHAR* panelName, int32 ZOrder = 0)
	{
		if (_tcslen(panelName) == 0)
			return nullptr;

		TObjectPtr<UUserWidget> userWidget = nullptr;

		UClass* widgetClass = T::StaticClass();

		for (const auto& pair : cachedUI)
		{
			if (pair.Key->IsChildOf(widgetClass))
			{
				userWidget = pair.Value;
				break;
			}
		}

		if (userWidget == nullptr)
		{
			FString ui_Path(UI_PATH);
			ui_Path.Append(panelName);
			UClass* loadWidgetClass = LoadClass<UUserWidget>(nullptr, *ui_Path);

			userWidget = cachedUI.Add(loadWidgetClass, CreateWidget(GetWorld(), loadWidgetClass));
		}

		Show(userWidget, ZOrder);

		return Cast<T>(userWidget);
	}

	// Show widgetClass Return T Class
	template<typename T>
	T* Show(UClass* widgetClass, int32 ZOrder = 0)
	{
		return Cast<T>(Show(widgetClass, ZOrder));
	}

	// Show widgetClass
	UUserWidget* Show(UClass* widgetClass, int32 ZOrder = 0);

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
	void Show(TObjectPtr<UUserWidget>& userWidget, int32 ZOrder);
private:
	TDoubleLinkedList<TObjectPtr<UUserWidget>> activeUIList;

	TMap<TObjectPtr<UClass>, TObjectPtr<UUserWidget>> cachedUI;

	FActiveEvent showEvent;
	FActiveEvent hideEvent;

	const TCHAR* UI_PATH;
};
