// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTT_WaitAnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "GameFramework/Character.h"

UBTT_WaitAnimMontage::UBTT_WaitAnimMontage()
{
	bNotifyTick = 1;
	bTickIntervals = true;
}

EBTNodeResult::Type UBTT_WaitAnimMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ACharacter* character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;
	
	animInstance = character->GetMesh()->GetAnimInstance();
	if (animInstance == nullptr)
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTT_WaitAnimMontage::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ensure(animInstance->Montage_IsPlaying(nullptr));

	UE_LOG(LogTemp, Log, TEXT("Tlqkf"));
	animInstance = nullptr;
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
