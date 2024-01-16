// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/AnimNotifies/AnimNotify_MultiHitBoxAttack.h"
#include "AnimNotify_FistAttack.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UAnimNotify_FistAttack : public UAnimNotify_MultiHitBoxAttack
{
	GENERATED_BODY()
protected:
	virtual void BeginAttack(class UCharacterCombatComponent* characterCombatComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitBox, meta = (AllowPrivateAccess = "true"))
	uint8 animNotifyIndex = 0;
};
