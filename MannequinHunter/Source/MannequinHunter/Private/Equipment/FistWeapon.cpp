// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/FistWeapon.h"
#include "Equipment/HitBoxActor.h"
#include "Gameframework/Character.h"

AFistWeapon::AFistWeapon()
{


}

void AFistWeapon::SetActiveCylinderIndex(uint8 index)
{
	EFistWeaponSlotFlag eIndex = StaticCast<EFistWeaponSlotFlag>(index);
	AddActiveCylinderIndexQueue(eIndex, EFistWeaponSlotFlag::L_Fist, EFistWeaponSlot::L_Fist);
	AddActiveCylinderIndexQueue(eIndex, EFistWeaponSlotFlag::R_Fist, EFistWeaponSlot::R_Fist);
	AddActiveCylinderIndexQueue(eIndex, EFistWeaponSlotFlag::L_Leg, EFistWeaponSlot::L_Leg);
	AddActiveCylinderIndexQueue(eIndex, EFistWeaponSlotFlag::R_Leg, EFistWeaponSlot::R_Leg);
}

void AFistWeapon::SetWeaponOwner(AActor* weaponOwner)
{
	ACharacter* character = Cast<ACharacter>(weaponOwner);
	if (character)
	{
		//for (const FFistHitBoxData& hitBox : fistWeaponData.useHitBoxData)
		USkeletalMeshComponent* mesh = character->GetMesh();
		for(int i = 0 ; i < fistWeaponData.useHitBoxData.Num(); i++)
		{
			SetupCylinderAttachment(multiHitBoxWeaponData.hitBoxs[i], mesh, fistWeaponData.useHitBoxData[i].socketNames);
		}
	}
	Super::SetWeaponOwner(weaponOwner);
}

void AFistWeapon::CreateHitBox()
{

	for (const FFistHitBoxData& hitBox : fistWeaponData.useHitBoxData)
	{
		multiHitBoxWeaponData.hitBoxs.Add(GetWorld()->SpawnActor<AHitBoxActor>(hitBox.hitBox));
		
	}

}

void AFistWeapon::AddActiveCylinderIndexQueue(EFistWeaponSlotFlag index, EFistWeaponSlotFlag flag, EFistWeaponSlot slot)
{
	if ((index & flag) != EFistWeaponSlotFlag::None)
		multiHitBoxWeaponData.activeCylinderIndexQueue.Enqueue(StaticCast<uint8>(slot));
}
