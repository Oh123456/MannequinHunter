// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_IsPlayAnimMontage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BaseActionCharacter.h"

bool UBTD_IsPlayAnimMontage::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ACharacter* character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return false;

	UAnimInstance* animInstance = character->GetMesh()->GetAnimInstance();
	if (animInstance == nullptr)
		return false;

	return animInstance->Montage_IsPlaying(checkMontage);
	
}
