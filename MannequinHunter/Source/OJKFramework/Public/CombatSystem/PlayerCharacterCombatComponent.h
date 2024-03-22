// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "PlayerCharacterCombatComponent.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_RetVal(class UCameraComponent*, FOnFindCameraComponent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OJKFRAMEWORK_API UPlayerCharacterCombatComponent : public UCharacterCombatComponent
{
	GENERATED_BODY()

public:
	UPlayerCharacterCombatComponent();


	const FOnFindCameraComponent& OnFindCameraComponent() { return findCameraComponentDelegate; }
private:
	UFUNCTION()
	void RecoverStamina();
public:
	virtual void SetLockOnTarget() override;

protected:
	virtual void BeginPlay() override;

	virtual int32 CalculateRecoveryStamina();
private:
	FOnFindCameraComponent findCameraComponentDelegate;

	float LockOnLength;

	TArray<AActor*> lockOnTargetIgnoreActor;
	
	FTimerHandle staminaTimerHandle;
private:
	UPROPERTY(EditDefaultsOnly, Category = Recover, meta = (AllowPrivateAccess = "true"))
	float recoveryStaminaTime = 0.2f;
	UPROPERTY(EditDefaultsOnly, Category = Recover, meta = (AllowPrivateAccess = "true"))
	int32 recoveryStamina = 10;

	UPROPERTY(EditDefaultsOnly, Category = LockOn, meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> lockOnTargetObjectType;
};
