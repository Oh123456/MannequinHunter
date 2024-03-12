// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionObject/AnimNotifyFunctionObject.h"
#include "AN_FunctionObject_ChangeEnum.generated.h"

/**
 * 
 */
UCLASS(abstract)
class MANNEQUINHUNTER_API UAN_FunctionObject_ChangeEnum : public UAnimNotifyFunctionObject
{
	GENERATED_BODY()
	
protected:
	virtual void Execute(UAnimNotify* animNotify, USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference) override;
	virtual void ChangeEnum(int64 value, USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference) {}
};
