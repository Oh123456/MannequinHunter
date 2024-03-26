// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class MANNEQUINHUNTER_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

private:
	UFUNCTION()
	void MoveDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	virtual void BeginPlay() override;
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr <class UStaticMeshComponent> doorWallMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr <class UStaticMeshComponent> doorMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr <class UDoorObjectComponent> doorObjectComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr <class UBoxComponent> trigger;
};
