// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Defines.h"
#include "BTS_Pattern.generated.h"

/**
 * 
 */


UCLASS()
class MANNEQUINHUNTER_API UBTS_Pattern : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTS_Pattern();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void SetOwner(AActor* ActorOwner) override;
private:
	UPROPERTY()
	const class UAIPattern* patternClass;
	UPROPERTY()
	const class AActor* actorOwner;
};
