// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DT_SuperArmorBreakInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDT_SuperArmorBreakInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MANNEQUINHUNTER_API IDT_SuperArmorBreakInterface
{
	GENERATED_BODY()
public:

	virtual float ExecuteSuperArmorBreakDamageType(float damageAmount,class UCombatComponent* damagedCombatSystem, AController* eventInstigator, AActor* damageCauser) = 0;
};
