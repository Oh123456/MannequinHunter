// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/MultiHitBoxWeapon.h"
#include "FistWeapon.generated.h"

/**
 * 
 */

class UShapeComponent;
UENUM(BlueprintType)
enum class EFistWeaponSlot : uint8
{
	L_Fist,
	R_Fist,
	L_Leg,
	R_Leg
};

UCLASS()
class MANNEQUINHUNTER_API AFistWeapon : public AMultiHitBoxWeapon
{
	GENERATED_BODY()
	

public:
	AFistWeapon();


private:


};
