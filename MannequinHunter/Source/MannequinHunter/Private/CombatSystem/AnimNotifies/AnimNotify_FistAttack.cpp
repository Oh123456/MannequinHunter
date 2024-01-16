// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotify_FistAttack.h"
#include "CombatSystem/FistCombatAnimationData.h"
#include "Equipment/FistWeapon.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "DebugLog.h"

void UAnimNotify_FistAttack::BeginAttack(UCharacterCombatComponent* characterCombatComponent)
{
	AFistWeapon* fistWeapon = Cast<AFistWeapon>(baseWeapon);
	UMannequinHunterCombatComponent* mannequinHunterCombatComponent = Cast<UMannequinHunterCombatComponent>(characterCombatComponent);
	if (fistWeapon && mannequinHunterCombatComponent)
	{
		UBaseCombatAnimationData* base = const_cast<UBaseCombatAnimationData*>(mannequinHunterCombatComponent->GetCombatAnimationData());
		UFistCombatAnimationData* combatAnimationData = Cast<UFistCombatAnimationData>(base);
		if (combatAnimationData)
		{
			const TArray<FFistAnimMontageHitBoxFlagArray>* hitBoxs = combatAnimationData->GetHitBoxSlotFlag(mannequinHunterCombatComponent->GetCurrentCombatMontageType());
			for (const FFistAnimMontageHitBoxFlagArray& flagArray : (*hitBoxs))
			{
				if (flagArray.flags.IsEmpty())
				{
					//UE_LOG_WARNING(LogTemp,TEXT("Anim Index : %d, HitBoxSlot Empty!!!" ), mannequinHunterCombatComponent->GetCombatAnimationData());
					continue;
				}
				//UE_LOG_WARNING(LogTemp,TEXT("FistWeapon hitBox Flag : %d" ), (flagArray.flags[animNotifyIndex].flag));
				fistWeapon->SetActiveCylinderIndex((flagArray.flags[animNotifyIndex].flag));
			}
		}
	}
	Super::BeginAttack(characterCombatComponent);

}
