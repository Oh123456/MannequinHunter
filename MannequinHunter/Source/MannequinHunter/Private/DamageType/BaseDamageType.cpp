// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageType/BaseDamageType.h"
#include "DamageType/DT_SuperArmorBreakInterface.h"
#include "DamageType/DT_StatusChangeInterface.h"
#include "Defines.h"


float UBaseDamageType::ExecuteDamageType(float damageAmount, UCombatComponent* damagedCombatSystem, AController* eventInstigator, AActor* damageCauser)
{
	float damage = damageAmount;
	UClass* myUClass = GetClass();
	EXECUTE_INTERFACE_RET_VAL(DT_SuperArmorBreakInterface, myUClass, ExecuteSuperArmorBreakDamageType, damage, damageAmount, damagedCombatSystem, eventInstigator, damageCauser)	
	EXECUTE_INTERFACE(DT_StatusChangeInterface, myUClass, ChangeStatus, eventInstigator)
	return damage;
}
