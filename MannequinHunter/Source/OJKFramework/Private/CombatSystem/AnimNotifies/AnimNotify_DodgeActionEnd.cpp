// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotify_DodgeActionEnd.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Utility/CombatSystemUtility.h"

void UAnimNotify_DodgeActionEnd::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	Super::Notify(meshComp, animation, eventReference);

	UCharacterCombatComponent* characterCombatComponent;
	if (!FCombatSystemUtility::IsCombatComponentValid(meshComp, nullptr, &characterCombatComponent))
		return;

	if (characterCombatComponent->IsLockOn())
		characterCombatComponent->SetIsActorRotation(true);
	characterCombatComponent->SeCombatAbleDefault();
}