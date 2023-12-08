// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotifyState_Attack.h"
#include "Utility/CombatSystemUtility.h"
#include "Equipment/BaseWeapon.h"
#include "CombatSystem/CharacterCombatComponent.h"

UAnimNotifyState_Attack::UAnimNotifyState_Attack() : Super(),
baseWeapon(nullptr)
{
	NotifyColor = FColor::Silver;
	//GetNotifyName
}

void UAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration, const FAnimNotifyEventReference& eventReference)
{
	Super::NotifyBegin(meshComp, animation, totalDuration, eventReference);
	UCombatComponent* combatComponent;
	if (FCombatSystemUtility::IsCombatComponentValid(meshComp, OUT & combatComponent))
	{
		UCharacterCombatComponent* characterCombat = Cast<UCharacterCombatComponent>(combatComponent);
		if (characterCombat == nullptr)
			return;

		baseWeapon = Cast<ABaseWeapon>(characterCombat->GetEquipment(ECombatEquipmentSlot::E_MainWeapon));

		BeginAttack(characterCombat);
	}
	

}

void UAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float frameDeltaTime, const FAnimNotifyEventReference& eventReference)
{
	Super::NotifyTick(meshComp, animation, frameDeltaTime, eventReference);
	if (baseWeapon)
		baseWeapon->HitCheck();
}

void UAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	Super::NotifyEnd(meshComp, animation, eventReference);

	if (baseWeapon)
		baseWeapon->HitCheckEnd();
	baseWeapon = nullptr;
}

void UAnimNotifyState_Attack::BeginAttack(UCharacterCombatComponent* characterCombatComponent)
{
	
	if (baseWeapon)
		baseWeapon->HitCheckBegin();
}

