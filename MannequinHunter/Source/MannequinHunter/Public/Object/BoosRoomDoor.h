// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/TwoTriggerDoor.h"
#include "BoosRoomDoor.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API ABoosRoomDoor : public ATwoTriggerDoor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void BossMove(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, Category = Door, meta = (AllowPrivateAccess = "true"))
	FName bossName;
};
