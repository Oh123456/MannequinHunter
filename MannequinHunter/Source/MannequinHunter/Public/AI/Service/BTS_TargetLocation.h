// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_TargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UBTS_TargetLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTS_TargetLocation();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector moveLocation;
};
