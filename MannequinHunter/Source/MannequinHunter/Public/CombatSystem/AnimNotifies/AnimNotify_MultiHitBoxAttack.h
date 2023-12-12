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
public:
	UAnimNotify_MultiHitBoxAttack();
protected:
	virtual void BeginAttack(class UCharacterCombatComponent* characterCombatComponent) override; 
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitBox, meta = (AllowPrivateAccess = "true"))
	TArray<uint8> hitBoxSlot;
};
