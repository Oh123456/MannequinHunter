// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifies/AnimNotify_ControlAble.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Player/PlayerCharacter.h"
#include "Utility/CombatSystemUtility.h"
#include "Character/PlayerCommonEnums.h"


void UAnimNotify_ControlAble::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	Super::Notify(meshComp, animation, eventReference);

	UCharacterCombatComponent* characterCombatComponent;
	ABaseActionCharacter* character;
	if (!FCombatSystemUtility::IsCombatComponentValid(meshComp, OUT & character, OUT & characterCombatComponent))
		return;

	if (characterCombatComponent->IsLockOn())
		characterCombatComponent->SetIsActorRotation(true);

	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(character);
	if (playerCharacter)
	{
		UHFSMComponent* hfsm = playerCharacter->GetHFSM();
		if (hfsm)
		hfsm->SetStateOrder(EStateOrder::Idle);
	}

}
