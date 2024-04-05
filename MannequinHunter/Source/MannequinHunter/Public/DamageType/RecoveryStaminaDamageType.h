// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageType/BaseDamageType.h"
#include "DT_StatusChangeInterface.h"
#include "RecoveryStaminaDamageType.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API URecoveryStaminaDamageType : public UBaseDamageType , public IDT_StatusChangeInterface
{
	GENERATED_BODY()
public:
	virtual void ChangeStatus(AController* eventInstigator) override;
};
