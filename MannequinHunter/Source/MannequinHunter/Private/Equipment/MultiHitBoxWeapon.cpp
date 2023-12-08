// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/MultiHitBoxWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Equipment/HitBoxActor.h"

void AMultiHitBoxWeapon::SetupCylinderAttachment(TSubclassOf<AHitBoxActor> createHitBox ,USceneComponent* InParent, FName InSocketName)
{
	AHitBoxActor* hitBox = GetWorld()->SpawnActor<AHitBoxActor>(createHitBox);

	hitBox->AttachToComponent(InParent, FAttachmentTransformRules::KeepRelativeTransform, InSocketName);
	multiHitBoxWeaponData.hitBoxs.Add(hitBox);

}

void AMultiHitBoxWeapon::SetCylinderActive(bool isActive)
{
	if (multiHitBoxWeaponData.hitBoxs.Num() <= 0)
		return;
	uint8 index = 0;

	if (isActive)
	{
		while (activeCylinderIndexQueue.Dequeue(index))
		{
			multiHitBoxWeaponData.hitBoxs[index]->SetCylinderActive(isActive);
			hideCylinderIndexQueue.Dequeue(index);
		}
	}
	else
	{
		if (activeCylinderIndexQueue.IsEmpty())
		{
			for(AHitBoxActor* hitBox : multiHitBoxWeaponData.hitBoxs)
				hitBox->SetCylinderActive(isActive);
		}
		else
		{
			while (activeCylinderIndexQueue.Dequeue(index))
			{
				multiHitBoxWeaponData.hitBoxs[index]->SetCylinderActive(isActive);
			}
		}
	}
}

void AMultiHitBoxWeapon::SetCylinder()
{
	for (const TObjectPtr<AHitBoxActor> hitBox : multiHitBoxWeaponData.hitBoxs)
	{
		hitBox->GetHitBox()->OnComponentBeginOverlap.AddDynamic(this, &AMultiHitBoxWeapon::HitCheckCylinder);
	}
	
}

void AMultiHitBoxWeapon::SetTraceHit()
{
	Super::SetTraceHit();
}

bool AMultiHitBoxWeapon::CheckCylinderComponent()
{
	return multiHitBoxWeaponData.hitBoxs.Num() > 0;
}
