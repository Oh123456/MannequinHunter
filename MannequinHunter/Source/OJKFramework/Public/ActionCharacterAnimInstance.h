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

private:
	void SetBlendSpaceValue(const class UCharacterMovementComponent* const characterMovement);
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	virtual void SetSpeed(const UCharacterMovementComponent* characterMovement);
	virtual void SetAngle(const UCharacterMovementComponent* characterMovement);
protected:
	TObjectPtr<ABaseActionCharacter> ownerCharacter;

private:
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float angle;
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float speed;
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool isFalling;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	FVector velocity;
};