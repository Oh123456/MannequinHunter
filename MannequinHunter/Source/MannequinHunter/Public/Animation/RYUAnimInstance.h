// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacterAnimInstance.h"
#include "RYUAnimInstance.generated.h"

/**
 * 
 */

//enum ERYUWeaponType;

UCLASS()
class MANNEQUINHUNTER_API URYUAnimInstance : public UPlayerCharacterAnimInstance
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintPure, Category = WeaponType , meta = (BlueprintThreadSafe))
	ERYUWeaponType GetWeaponType();

public:
	virtual void NativeUpdateAnimation(float deltaSeconds) override;
private:
	UPROPERTY(BlueprintReadOnly, Category = WeaponType, meta = (AllowPrivateAccess = "true"))
	ERYUWeaponType weaponType;
};
