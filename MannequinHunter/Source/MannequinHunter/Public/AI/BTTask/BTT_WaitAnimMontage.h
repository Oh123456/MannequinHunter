// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_WaitAnimMontage.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UBTT_WaitAnimMontage : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_WaitAnimMontage();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<class UAnimInstance> animInstance;
};
