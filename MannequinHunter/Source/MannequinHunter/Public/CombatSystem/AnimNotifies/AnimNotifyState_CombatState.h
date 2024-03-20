// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Defines.h"
#include "AnimNotifyState_CombatState.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UAnimNotifyState_CombatState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UAnimNotifyState_CombatState();
public:
	virtual void BeginDestroy() override;

private:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, Category = CombatState ,meta = (AllowPrivateAccess = "true"))
	bool isSuperArmor = true;
	UPROPERTY(EditAnywhere, Category = CombatState, meta = (AllowPrivateAccess = "true"))
	bool isInvincibility = false;
	UPROPERTY()
	class UCharacterCombatComponent* characterCombatComponent = nullptr;
};
