// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsPlayAnimMontage.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UBTD_IsPlayAnimMontage : public UBTDecorator
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
private:
	TObjectPtr<class UAnimMontage> checkMontage = nullptr;
};
