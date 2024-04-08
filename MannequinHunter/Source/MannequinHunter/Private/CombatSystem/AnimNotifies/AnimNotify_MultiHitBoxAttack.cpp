// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotify_MultiHitBoxAttack.h"
#include "Equipment/MultiHitBoxWeapon.h"
#include "Math/Color.h"

UAnimNotify_MultiHitBoxAttack::UAnimNotify_MultiHitBoxAttack()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::Red;
#endif
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
