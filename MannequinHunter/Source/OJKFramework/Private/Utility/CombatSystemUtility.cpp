// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/CombatSystemUtility.h"
#include "GameFramework/Actor.h"
#include "BaseActionCharacter.h"
#include "CombatSystem/CombatComponent.h"
#include "Components/PrimitiveComponent.h"

bool FCombatSystemUtility::IsCombatComponentValid(UPrimitiveComponent* MeshComp)
{
	if (MeshComp == nullptr)
		return false;

	return ((MeshComp->GetOwner()->GetComponentByClass<UCombatComponent>()) != nullptr);
}

bool FCombatSystemUtility::IsCombatComponentValid(UPrimitiveComponent* MeshComp, OUT UCombatComponent** ownerCombatComponent)
{
	if (MeshComp == nullptr)
		return false;

	UCombatComponent* combatComponent = MeshComp->GetOwner()->GetComponentByClass<UCombatComponent>();

	if (combatComponent == nullptr)
		return false;

	if (ownerCombatComponent != nullptr)
		*ownerCombatComponent = combatComponent;

	return true;
}

bool FCombatSystemUtility::IsCombatComponentValid(UPrimitiveComponent* MeshComp, OUT ABaseActionCharacter** ownerCharacter, OUT UCharacterCombatComponent** ownerCombatComponent)
{
	ABaseActionCharacter* character = Cast<ABaseActionCharacter>(MeshComp->GetOwner());

	if (character == nullptr)
		return false;


	if (ownerCharacter != nullptr)
		*ownerCharacter = character;

	UCharacterCombatComponent* characterCombatComponent = character->GetCombatComponent();

	if (characterCombatComponent == nullptr)
		return false;

	if (ownerCombatComponent != nullptr)
		*ownerCombatComponent = characterCombatComponent;

	return true;
}
