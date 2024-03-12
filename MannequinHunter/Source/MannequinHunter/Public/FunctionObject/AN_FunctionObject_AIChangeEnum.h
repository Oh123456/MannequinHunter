// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionObject/AN_FunctionObject_ChangeEnum.h"
#include "Defines.h"
#include "AN_FunctionObject_AIChangeEnum.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MANNEQUINHUNTER_API UAN_FunctionObject_AIChangeEnum : public UAN_FunctionObject_ChangeEnum
{
	GENERATED_BODY()
	
protected:
	virtual void ChangeEnum(int64 value, USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference);
private:
	UPROPERTY(EditDefaultsOnly, meta = (ALLOW_PRIVATE_ACCESS))
	FName blackBoardKeyName;
};
