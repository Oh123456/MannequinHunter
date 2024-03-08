// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Defines.h"
#include "BTS_Pattern.generated.h"

/**
 * 
 */

//struct FPatternData
//{
//	FPatternData()
//	{
//
//	}
//
//	FPatternData(const FName& name, float weight)
//	{
//		this->weight = weight;
//		this->nameKey = name;
//	}
//
//
//	float weight;
//	FName nameKey;
//};

UCLASS()
class MANNEQUINHUNTER_API UBTS_Pattern : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_Pattern();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	virtual void SetOwner(AActor* ActorOwner) override;
private:
	//TArray<FPatternData> patternDatas;
private:
	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (ALLOW_PRIVATE_ACCESS))
	TArray<FName> patternNames;

};
