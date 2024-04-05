// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageType/BaseDamageType.h"
#include "DamageType/DT_SuperArmorBreakInterface.h"
#include "SuperDamageType.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API USuperDamageType : public UBaseDamageType , public IDT_SuperArmorBreakInterface
{
	GENERATED_BODY()
	
public:
	virtual float ExecuteSuperArmorBreakDamageType(float damageAmount, class UCombatComponent* damagedCombatSystem, AController* eventInstigator, AActor* damageCauser)  override;
private:
	float damageMultiplier = 1.2f;

};
