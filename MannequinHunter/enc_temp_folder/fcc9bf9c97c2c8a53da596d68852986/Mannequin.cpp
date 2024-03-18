// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Mannequin.h"
#include "CombatSystem/AICombatComponent.h"
#include "CombatSystem/CharacterCombatComponent.inl"
#include "Equipment/BlueprintBaseWeapon.h"
#include "DebugLog.h"

void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	ABlueprintBaseWeapon* weapon = combatComponent->CreateEquipment<ABlueprintBaseWeapon>(weaponClass, ECombatEquipmentSlot::E_MainWeapon);

	weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("Weapon_r"));
	weapon->SetWeaponOwner(this);
	//weapon->SetActorLocation(FVector(0.0f, 50.0f, 0.0f));
	//weapon->SetActorRotation(FRotator(0.0f, 0.0f, 90.0f));
}
