// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "MannequinHunterPlayerCharacter.generated.h"

enum class EPlayerInputType : uint8;

UCLASS()
class MANNEQUINHUNTER_API AMannequinHunterPlayerCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

protected:
	virtual void SetInputAction();

	virtual void ToggleCombat();

	virtual void InputJumpKey();
	virtual void InputJumpKeyCompleted();
	virtual void Dodge(const struct FInputActionInstance& inputActionInstance);
	virtual void LAttack(const struct FInputActionInstance& inputActionInstance);
	virtual void RAttack(const struct FInputActionInstance& inputActionInstance);

	virtual void Attack(EPlayerInputType type);
	virtual void LockOn();

	void OnInventory();
	void OnInfo();
};
