// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ActionCharacterAnimInstance.generated.h"

/**
 * 
 */
class ABaseActionCharacter;


UCLASS()
class OJKFRAMEWORK_API UActionCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure, Category = CombatCharacter, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetAngle() { return angle; }

	UFUNCTION(BlueprintPure, Category = CombatCharacter, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() { return speed; }

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	void SetBlendSpaceValue();
protected:
	TObjectPtr<ABaseActionCharacter> ownerCharacter;

private:
	float angle;
	float speed;
};