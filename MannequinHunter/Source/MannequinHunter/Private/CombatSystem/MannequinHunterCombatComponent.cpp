// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Singleton/CommandListManager.h"

UMannequinHunterCombatComponent::~UMannequinHunterCombatComponent()
{

}

void UMannequinHunterCombatComponent::ResetCommandList()
{
	if (currentCommandListTree)
		currentCommandListNode = currentCommandListTree->GetRoot(); 
}

ECharacterCombatMontageType UMannequinHunterCombatComponent::GetCommandMontageType()
{
	return GetCommandMontageType(playerInputType);	
}

ECharacterCombatMontageType UMannequinHunterCombatComponent::GetCommandMontageType(EPlayerInputType input)
{
	if (currentCommandListTree && currentCommandListNode)
	{
		const TSharedPtr<CommandListNode>* nextCommandListNode =  currentCommandListNode->FindChild(input);
		if (nextCommandListNode)
		{
			currentCommandListNode = *nextCommandListNode;
			return *(currentCommandListNode->GetValue()->Get());
		}
	}
	return ECharacterCombatMontageType::None;
}

void UMannequinHunterCombatComponent::ChangeCommandList(EWeaponType type)
{
	currentCommandListTree = *FCommandListManager::GetInstance()->GetCommandList(type);
	currentCommandListNode = currentCommandListTree->GetRoot();
}

void UMannequinHunterCombatComponent::BeginPlay()
{
	Super::BeginPlay();


	OnChangeWeaponType.AddUObject(this,&UMannequinHunterCombatComponent::ChangeCommandList);
}


