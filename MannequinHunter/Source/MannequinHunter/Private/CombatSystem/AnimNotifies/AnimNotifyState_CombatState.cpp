// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AnimNotifies/AnimNotifyState_CombatState.h"
#include "Utility/CombatSystemUtility.h"
#include "Math/Color.h"
#include "CombatSystem/CharacterCombatComponent.h"

UAnimNotifyState_CombatState::UAnimNotifyState_CombatState()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::Green;
#endif
}

void UAnimNotifyState_CombatState::BeginDestroy()
{
	Super::BeginDestroy();
	characterCombatComponent = nullptr;
}

void UAnimNotifyState_CombatState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (!FCombatSystemUtility::IsCombatComponentValid(MeshComp, nullptr, &characterCombatComponent))
		return;

	characterCombatComponent->SetSuperArmor(isSuperArmor);
	characterCombatComponent->SetImmortality(isInvincibility);
}

void UAnimNotifyState_CombatState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (characterCombatComponent)
	{
		characterCombatComponent->SetSuperArmor(false);
		characterCombatComponent->SetImmortality(false);
	}
}
