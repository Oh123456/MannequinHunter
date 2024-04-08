// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotify_ChangeEnum.h"
#include "FunctionObject/AnimNotifyFunctionObject.h"

void UAnimNotify_ChangeEnum::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (enumValue == nullptr)
		return;
	UAnimNotifyFunctionObject* notifyFunctionObject = Cast<UAnimNotifyFunctionObject>(functionObject->GetDefaultObject());
	if (notifyFunctionObject)
	{
		(*notifyFunctionObject)(this, MeshComp, Animation, EventReference);
	}
}

void UAnimNotify_ChangeEnum::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property->GetFName() != GET_MEMBER_NAME_CHECKED(UAnimNotify_ChangeEnum, enumClassName))
		return;
	if (enumClassName.IsNone())
		return;
	enumValue = FindObject<UEnum>(ANY_PACKAGE, *enumClassName.ToString());
}

