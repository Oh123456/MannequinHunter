// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/UISubsystem.h"
#include "Blueprint/UserWidget.h"


UUISubsystem::UUISubsystem() : Super(),
UI_PATH(TEXT("/Game/BP/HUD/"))
{

}

UUserWidget* UUISubsystem::Show(UClass* widgetClass, int32 ZOrder)
{

	if (widgetClass == nullptr)
		return nullptr;

	TObjectPtr<UUserWidget>* userWidget = cachedUI.Find(widgetClass);
	if (userWidget == nullptr)
	{
		userWidget = &cachedUI.Add(widgetClass, CreateWidget(GetWorld(), widgetClass));
	}

	Show(*userWidget,ZOrder);

	return *userWidget;
}

void UUISubsystem::Hide()
{
	if (activeUIList.IsEmpty())
		return;
	auto tail = activeUIList.GetTail();
	TObjectPtr<UUserWidget> widget = tail->GetValue();
	widget->RemoveFromParent();
	activeUIList.RemoveNode(tail);
	hideEvent.Broadcast(widget);
}

void UUISubsystem::Hide(UClass* widgetClass)
{
	if (activeUIList.IsEmpty())
		return;

	auto currentNode = activeUIList.GetHead();
	while (currentNode)
	{
		TObjectPtr<UUserWidget> value = currentNode->GetValue();
		if (value->GetClass() == widgetClass)
		{
			value->RemoveFromParent();
			activeUIList.RemoveNode(currentNode);
			hideEvent.Broadcast(value);
			break;
		}

		currentNode = currentNode->GetNextNode();
	}

}

bool UUISubsystem::IsShow(UClass* widgetClass)
{
	if (activeUIList.IsEmpty())
		return false;

	auto node = activeUIList.GetHead();

	while (node)
	{
		TObjectPtr<UUserWidget> value = node->GetValue();
		if (value->GetClass() == widgetClass)
		{
			return value->IsInViewport();
		}

		node = node->GetNextNode();
	}

	return false;
}

TDoubleLinkedList<TObjectPtr<UUserWidget>>::TDoubleLinkedListNode* UUISubsystem::CheckActiveList(TObjectPtr<UUserWidget>* ui)
{
	auto node = activeUIList.GetHead();
	while (node)
	{
		if (node->GetValue() == *ui)
		{
			return node;
		}

		node = node->GetNextNode();
	}
	return nullptr;
}

void UUISubsystem::Show(TObjectPtr<UUserWidget>& userWidget, int32 ZOrder)
{
	if ((userWidget)->IsInViewport())
	{
		auto activeUINode = CheckActiveList(&userWidget);

		if (activeUINode)
		{
			(userWidget)->RemoveFromParent();
			activeUIList.RemoveNode(activeUINode);
		}
	}

	(userWidget)->AddToViewport(ZOrder);
	activeUIList.AddTail((userWidget));
	showEvent.Broadcast(userWidget);
}

