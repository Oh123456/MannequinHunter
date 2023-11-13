// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetCombatSystemLibrary.h"
#include "Equipment/BaseWeapon.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "CombatSystem/CharacterCombatComponent.inl"

AEquipment* UKismetCombatSystemLibrary::CreateMainWeapon(UCharacterCombatComponent* characterCombat, TSubclassOf<ABaseWeapon> staticClass)
{
	TSubclassOf<AEquipment> equipment = staticClass;
	return characterCombat->CreateEquipment<FEquipmentItem>(equipment, ECombatEquipmentSlot::E_MainWeapon);
}
