// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/MultiHitBoxWeapon.h"
#include "FistWeapon.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EFistWeaponSlot : uint8
{
	L_Fist,
	R_Fist,
	L_Leg,
	R_Leg
};

USTRUCT()
struct FFistHitBoxData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHitBoxActor> hitBox;

	UPROPERTY(EditDefaultsOnly)
	FName socketNames;
};


USTRUCT()
struct FFistWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FFistHitBoxData> useHitBoxData;
};

UCLASS()
class MANNEQUINHUNTER_API AFistWeapon : public AMultiHitBoxWeapon
{
	GENERATED_BODY()
	

public:
	AFistWeapon();

public:
	virtual void SetWeaponOwner(class AActor* weaponOwner) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = HitBox, meta = (AllowPrivateAccess = "true"))
	FFistWeaponData fistWeaponData;
};
