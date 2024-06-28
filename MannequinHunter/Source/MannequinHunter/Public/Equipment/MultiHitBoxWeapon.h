// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/BaseWeapon.h"
#include "MultiHitBoxWeapon.generated.h"

/**
 * 
 */

struct FMultiHitBoxWeaponData
{
	TQueue<uint8> activeCylinderIndexQueue;
	TQueue<uint8> hideCylinderIndexQueue;

	UPROPERTY()
	TArray<TObjectPtr<class AHitBoxActor>> hitBoxs = {};
};

struct FMultiHitData
{
	UPROPERTY()
	TObjectPtr<class AHitBoxActor> hitDirectionHitBoxActor = nullptr;
};

UCLASS()
class MANNEQUINHUNTER_API AMultiHitBoxWeapon : public ABaseWeapon
{
	GENERATED_BODY()
public:
	virtual void SetActiveCylinderIndex(uint8 index) { multiHitBoxWeaponData.activeCylinderIndexQueue.Enqueue(index); }
	
public:
	virtual void SetCylinderActive(bool isActive) override;
	virtual FVector2D GetAttackDirection() const override;
	virtual FVector GetHitPoint() const;
	virtual void RemoveWeaponOwner() override;
protected:
	virtual void SetCylinder() override;
	virtual void SetTraceHit() override;
	virtual bool CheckCylinderComponent() override;
	virtual void BeginPlay()  override;
	virtual void CreateHitBox() {};
public:
	UFUNCTION(BlueprintCallable)
	void SetupCylinderAttachment(AHitBoxActor* hitbox ,USceneComponent* InParent, FName InSocketName);
	void ReleaseCylinder();
protected:
	FMultiHitBoxWeaponData multiHitBoxWeaponData;
	FMultiHitData multiHitData;
};
