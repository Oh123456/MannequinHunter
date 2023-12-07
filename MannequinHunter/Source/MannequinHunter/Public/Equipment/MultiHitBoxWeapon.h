// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/BaseWeapon.h"
#include "MultiHitBoxWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API AMultiHitBoxWeapon : public ABaseWeapon
{
	GENERATED_BODY()
public:
	void SetActiveCylinderIndex(uint8 index) { activeCylinderIndexQueue.Enqueue(index); }
	
public:
	virtual void SetCylinderActive(bool isActive) override;
protected:
	virtual void SetCylinder() override;
	virtual void SetTraceHit() override;
public:
	UFUNCTION(BlueprintCallable)
	void SetupCylinderAttachment(TSubclassOf<AHitBoxActor> createHitBox, USceneComponent* InParent, FName InSocketName);
private:
	TQueue<uint8> activeCylinderIndexQueue;
	TQueue<uint8> hideCylinderIndexQueue;
protected:

	//UPROPERTY(VisibleAnywhere, Category = Cylinder)
	//TArray<TObjectPtr<class UShapeComponent>> cylinderComponents = {};

	UPROPERTY()
	TArray<TObjectPtr<class AHitBoxActor>> hitBoxs = {};
};
