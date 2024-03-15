// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_BaseAnimation.h"
#include "BTT_PatternAction.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UBTT_PatternAction : public UBTT_BaseAnimation
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
