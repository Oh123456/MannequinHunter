// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ChangeEnum.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UBTT_ChangeEnum : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
	uint8 changeValue;
};
