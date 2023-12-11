// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/MultiHitBoxWeapon.h"
#include "FistWeapon.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EFistWeaponSlotFlag : uint8
{
	None = 0,
	L_Fist = 1,
	R_Fist = L_Fist << 1,
	L_Leg = L_Fist << 3,
	R_Leg = L_Fist << 4,
};

ENUM_CLASS_FLAGS(EFistWeaponSlotFlag)

UENUM(BlueprintType)
enum class EFistWeaponSlot : uint8
{
	L_Fist = 0,
	R_Fist,
	L_Leg,
	R_Leg,
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

private:
	void AddActiveCylinderIndexQueue(EFistWeaponSlotFlag index, EFistWeaponSlotFlag flag , EFistWeaponSlot slot);
public:
	virtual void SetActiveCylinderIndex(uint8 index) override;
	virtual void SetWeaponOwner(class AActor* weaponOwner) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = HitBox, meta = (AllowPrivateAccess = "true"))
	FFistWeaponData fistWeaponData;
};
