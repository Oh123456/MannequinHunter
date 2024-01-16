// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotify_MultiHitBoxAttack.h"
#include "Equipment/MultiHitBoxWeapon.h"

UAnimNotify_MultiHitBoxAttack::UAnimNotify_MultiHitBoxAttack()
{
	NotifyColor = FColor::Red;
}

void UAnimNotify_MultiHitBoxAttack::BeginAttack(UCharacterCombatComponent* characterCombatComponent)
{
	AMultiHitBoxWeapon* multiHitBoxWeapon = Cast<AMultiHitBoxWeapon>(baseWeapon);
	if (multiHitBoxWeapon)
	{
		for (const uint8 index : hitBoxSlot)
		{
			multiHitBoxWeapon->SetActiveCylinderIndex(index);
		}
	}
	Super::BeginAttack(characterCombatComponent);
}
