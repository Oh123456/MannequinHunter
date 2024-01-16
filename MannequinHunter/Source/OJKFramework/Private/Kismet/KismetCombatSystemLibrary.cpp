// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetCombatSystemLibrary.h"
#include "Equipment/BaseWeapon.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "CombatSystem/CharacterCombatComponent.inl"
#include "Player/PlayerCharacter.h"

AEquipment* UKismetCombatSystemLibrary::CreateMainWeapon(UCharacterCombatComponent* characterCombat, TSubclassOf<ABaseWeapon> staticClass)
{
	TSubclassOf<AEquipment> equipment = staticClass;
	return characterCombat->CreateEquipment<AEquipment>(equipment, ECombatEquipmentSlot::E_MainWeapon);
}

int32 UKismetCombatSystemLibrary::GetAttackCount(UCharacterCombatComponent* characterCombat)
{
	return characterCombat->GetAttackCount();
}

int32 UKismetCombatSystemLibrary::GetAttackCountFromPlayer(APlayerCharacter* player)
{
	return GetAttackCount(player->GetCombatComponent());
}
