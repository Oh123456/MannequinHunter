// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotifyState_InputBuffer.h"
#include "Controller/ActionPlayerController.h"

void UAnimNotifyState_InputBuffer::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration, const FAnimNotifyEventReference& eventReference)
{
	Super::NotifyBegin(meshComp, animation, totalDuration, eventReference);
	AActionPlayerController* controller = meshComp->GetOwner()->GetInstigatorController<AActionPlayerController>();
	if (controller)
		controller->SetIsAddableInputBuffer(true);
	
}

void UAnimNotifyState_InputBuffer::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	Super::NotifyEnd(meshComp, animation, eventReference);
	AActionPlayerController* controller = meshComp->GetOwner()->GetInstigatorController<AActionPlayerController>();
	if (controller)
		controller->SetIsAddableInputBuffer(false);

}
