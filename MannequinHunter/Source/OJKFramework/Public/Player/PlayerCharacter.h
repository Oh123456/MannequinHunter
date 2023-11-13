// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionCharacter.h"
#include "HFSM/HFSMComponent.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

UCLASS()
class OJKFRAMEWORK_API APlayerCharacter : public ABaseActionCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

public:
	UFUNCTION(BlueprintCallable , Category = PlayerCharacter)
	uint8 GetCurrentStateMachineID() { return HFSM->GetCurrentStateMachineID(); }
	UFUNCTION(BlueprintCallable, Category = PlayerCharacter)
	uint8 GetCurrentStateID() { return HFSM->GetCurrentStateID(); }

protected:
	// To add mapping context
	virtual void BeginPlay() override;
	virtual void Look(const FInputActionValue& Value);
	virtual void Move(const FInputActionValue& Value);

protected:
	TObjectPtr<UHFSMComponent> HFSM;

	FVector2D inputDirection;
};
