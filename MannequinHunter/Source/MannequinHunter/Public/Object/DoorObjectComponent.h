// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorObjectComponent.generated.h"

UCLASS()
class MANNEQUINHUNTER_API UDoorObjectComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UDoorObjectComponent();

	void SetDoorMesh(class UStaticMeshComponent* mesh) { doorObjectComponent = mesh; }

	void CallMoveDoor();

	void MoveDoorAtLocation(const FVector& location);

private:
	UFUNCTION()
	void MoveDoor();

	UFUNCTION()
	void MoveDoorAtLocation();

private:
	FTimerHandle doorTimerHandle;

private:
	FVector moveDoorAtLocation_Vector;
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UStaticMeshComponent> doorObjectComponent;
private:
	UPROPERTY(EditAnywhere, Category = Door, meta = (AllowPrivateAccess = "true"))
	FVector movePos;

	UPROPERTY(EditAnywhere, Category = Door, meta = (AllowPrivateAccess = "true"))
	FRotator moveRotator;

	UPROPERTY(EditAnywhere, Category = Door, meta = (AllowPrivateAccess = "true"))
	float interval = 0.02f;
	UPROPERTY(EditAnywhere, Category = Door, meta = (AllowPrivateAccess = "true"))
	float InterpSpeed = 1.2f;
};
