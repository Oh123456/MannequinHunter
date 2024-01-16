// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifies/AnimNotify_JumUp.h"
#include "GameFramework/Character.h"

void UAnimNotify_JumUp::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	Super::Notify(meshComp, animation, eventReference);

	ACharacter* character = Cast<ACharacter>(meshComp->GetOwner());
	if (character)
	{
		character->Jump();
	}
}
