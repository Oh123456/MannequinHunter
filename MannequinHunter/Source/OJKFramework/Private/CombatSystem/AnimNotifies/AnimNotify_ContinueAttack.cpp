// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotify_ContinueAttack.h"
#include "BaseActionCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Utility/CombatSystemUtility.h"

void UAnimNotify_ContinueAttack::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	Super::Notify(meshComp, animation, eventReference);
	UCharacterCombatComponent* characterCombatComponent;
	if (!FCombatSystemUtility::IsCombatComponentValid(meshComp, nullptr, &characterCombatComponent))
		return;

	characterCombatComponent->AddAttackCount();

}
