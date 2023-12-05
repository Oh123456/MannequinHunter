// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/MannequinHunterCombatComponent.h"

UMannequinHunterCombatComponent::~UMannequinHunterCombatComponent()
{
	ClearInputList();
}

void UMannequinHunterCombatComponent::AddInputList(EPlayerInputType type)
{
	if (inputListHead == nullptr)
	{
		inputListHead = new TList<EPlayerInputType>(type);
		return;
	}


	inputListHead->Next = new TList<EPlayerInputType>(type);

}

void UMannequinHunterCombatComponent::ClearInputList()
{
	if (inputListHead == nullptr)
		return;
	UnLinkInputList(inputListHead);
	inputListHead = nullptr;
}

void UMannequinHunterCombatComponent::UnLinkInputList(TList<EPlayerInputType>* list)
{
	if (list->Next)
		UnLinkInputList(list->Next);

	delete list->Next;
	list->Next = nullptr;
}
