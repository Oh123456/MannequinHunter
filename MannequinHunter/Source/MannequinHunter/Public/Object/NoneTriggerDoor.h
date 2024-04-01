// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoneTriggerDoor.generated.h"

UCLASS()
class MANNEQUINHUNTER_API ANoneTriggerDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoneTriggerDoor();

public:
	void MoveDoor();

protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr <class UStaticMeshComponent> doorWallMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr <class UStaticMeshComponent> doorMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr <class UDoorObjectComponent> doorObjectComponent;

};
