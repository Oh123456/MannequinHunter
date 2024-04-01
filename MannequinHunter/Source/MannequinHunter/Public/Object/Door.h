// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoneTriggerDoor.h"
#include "Door.generated.h"

UCLASS()
class MANNEQUINHUNTER_API ADoor : public ANoneTriggerDoor
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

	UPROPERTY(EditAnywhere)
	TObjectPtr <class UBoxComponent> trigger;
};
