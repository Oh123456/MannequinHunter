// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageType/ActionGameDamageTypeInterface.h"
#include "SuperDamageType.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API USuperDamageType : public UDamageType, public IActionGameDamageTypeInterface
{
	GENERATED_BODY()
	
public:
	virtual float ExecuteDamageType(float damageAmount, UCombatComponent* damagedCombatSystem, AController* eventInstigator, AActor* damageCauser) override;
private:
	float damageMultiplier = 1.2f;

};
