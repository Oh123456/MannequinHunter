// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
//#include "../AIPattern.h"
#include "BaseAIController.generated.h"

/**
 * 
 */


UCLASS()
class MANNEQUINHUNTER_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	const static FName STATE_ENUM;
	const static FName CHASE_ENUM_KEY;
	const static FName TARGET_ACTOR_KEY;
	const static FName INITIAL_LOCATION;

public:
	ABaseAIController();

	const class UAIPattern* GetAIPattern() const;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	virtual void LookTarget(AActor* actor, FAIStimulus stimulus);
	virtual void LostTarget(AActor* actor, FAIStimulus stimulus);

private:
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus);
protected:
	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<UAIPerceptionComponent> aiPerception;

	UPROPERTY(EditDefaultsOnly, Category = BlackBoard)
	FName AIPatternKey = TEXT("Pattern");
	UPROPERTY(EditDefaultsOnly, Category = BlackBoard)
	TSubclassOf<class UAIPattern> AIPattern;
private:
	UPROPERTY(EditAnywhere, Category = BehaviorTree, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> behaviorTree;

	UPROPERTY(EditAnywhere, Category = TargetTag, meta = (AllowPrivateAccess = "true"))
	TSet<FName> targetTags;
};
