// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionObject/AN_FunctionObject_ChangeEnum.h"
#include "CombatSystem/AnimNotifies/AnimNotify_ChangeEnum.h"

void UAN_FunctionObject_ChangeEnum::Execute(UAnimNotify* animNotify, USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	UAnimNotify_ChangeEnum* notify = Cast<UAnimNotify_ChangeEnum>(animNotify);
	if (notify)
	{
		int64 value = notify->GetEnumValue();
		if (value != -1)
			ChangeEnum(value, meshComp, animation, eventReference);
	}
}
