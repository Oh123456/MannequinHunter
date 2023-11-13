// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotify_LO_ActorRotation_Lock.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Utility/CombatSystemUtility.h"

void UAnimNotify_LO_ActorRotation_Lock::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	Super::Notify(meshComp, animation, eventReference);

	UCharacterCombatComponent* characterCombatComponent;
	if (!FCombatSystemUtility::IsCombatComponentValid(meshComp, nullptr, &characterCombatComponent))
		return;

	if (characterCombatComponent->IsLockOn())
		characterCombatComponent->SetIsActorRotation(false);

}