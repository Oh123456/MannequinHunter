// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/AnimNotifies/AnimNotifyState_Attack.h"
#include "AnimNotify_MultiHitBoxAttack.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UAnimNotify_MultiHitBoxAttack : public UAnimNotifyState_Attack
{
	GENERATED_BODY()
protected:
	virtual void BeginAttack(class UCharacterCombatComponent* characterCombatComponent) override; 
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitBox, meta = (AllowPrivateAccess = "true"))
	TArray<uint8> hitBoxSlot;
};
