// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Door.h"
#include "TwoTriggerDoor.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API ATwoTriggerDoor : public ADoor
{
	GENERATED_BODY()
public:
	ATwoTriggerDoor();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UBoxComponent> otherTrigger;
};
