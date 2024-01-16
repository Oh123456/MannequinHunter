// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_Attack.generated.h"

/**
 * 
 */
UCLASS()
class OJKFRAMEWORK_API UAnimNotifyState_Attack : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UAnimNotifyState_Attack();

private:

	virtual void NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration, const FAnimNotifyEventReference& eventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float frameDeltaTime, const FAnimNotifyEventReference& eventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference) override;

protected:
	virtual void BeginAttack(class UCharacterCombatComponent* characterCombatComponent);
protected:

	UPROPERTY()
	TObjectPtr<class ABaseWeapon> baseWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitBox, meta = (AllowPrivateAccess = "true"))
	bool isRotationLock;
};
