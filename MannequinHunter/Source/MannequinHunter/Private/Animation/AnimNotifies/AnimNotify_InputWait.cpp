// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifies/AnimNotify_InputWait.h"
#include "Player/PlayerCharacter.h"
#include "Character/PlayerCommonEnums.h"

void UAnimNotify_InputWait::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	Super::Notify(meshComp, animation, eventReference);


	APlayerCharacter* player = Cast<APlayerCharacter>(meshComp->GetOwner());
	if (player)
	{
		UHFSMComponent* hfsm = player->GetHFSM();
		if (hfsm)
			hfsm->SetStateOrder(EStateOrder::InputWait);
	}
}
