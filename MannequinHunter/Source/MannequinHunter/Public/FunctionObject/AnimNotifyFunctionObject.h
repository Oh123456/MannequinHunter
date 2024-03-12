// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AnimNotifyFunctionObject.generated.h"

/**
 * 
 */
UCLASS(abstract)
class MANNEQUINHUNTER_API UAnimNotifyFunctionObject : public UObject
{
	GENERATED_BODY()
	
public:
	void operator()(UAnimNotify* animNotify,USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
	{
		Execute(animNotify,meshComp, animation, eventReference);
	}

protected:
	virtual void Execute(UAnimNotify* animNotify, USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference) {}
};
