// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_BaseAnimation.generated.h"

enum class ECharacterCombatMontageType : uint8;
/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UBTT_BaseAnimation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

protected:
	void PlayAnimation(class ABaseEnemyCharacter* character, UBehaviorTreeComponent& OwnerComp, ECharacterCombatMontageType animSlot, float playRate = 1.0f);
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector enumKey;
};
