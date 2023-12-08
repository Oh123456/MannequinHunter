// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/FistWeapon.h"
#include "Equipment/HitBoxActor.h"
#include "Gameframework/Character.h"

AFistWeapon::AFistWeapon()
{


}

void AFistWeapon::SetWeaponOwner(AActor* weaponOwner)
{
	ACharacter* character = Cast<ACharacter>(weaponOwner);
	if (character)
	{
		for (const FFistHitBoxData& hitBox : fistWeaponData.useHitBoxData)
		{
			SetupCylinderAttachment(hitBox.hitBox, character->GetMesh(), hitBox.socketNames);
		}
	}
	Super::SetWeaponOwner(weaponOwner);
}
