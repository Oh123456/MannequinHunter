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

public:

	virtual void SetLockOnTarget() override;

protected:
	virtual void BeginPlay() override;

private:
	FOnFindCameraComponent findCameraComponentDelegate;

	float LockOnLength;

	TArray<AActor*> lockOnTargetIgnoreActor;
private:
	UPROPERTY(EditDefaultsOnly, Category = LockOn, meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> lockOnTargetObjectType;
};
