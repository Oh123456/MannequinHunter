// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionCharacter.h"
#include "HFSM/HFSMComponent.h"
#include "InputActionValue.h"
#include "Defines.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

class UInputAction;

USTRUCT(BlueprintType)
struct FPlayerInputData
{
	GENERATED_BODY()
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* jumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* moveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* lookAction;

	/** PlayerCombat NotCombat Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* combatAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* dodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Attack2Action;
};


UCLASS()
class OJKFRAMEWORK_API APlayerCharacter : public ABaseActionCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UHFSMComponent* GetHFSM() { return HFSM; }

	bool IsMoveInput() 
	{
		return !FVector2D::ZeroVector.Equals(inputDirection);
	}

	template<typename T>
	T GetCurrentStateMachineID() { return StaticCast<T>(HFSM->GetCurrentStateMachineID()); }



public:
	UFUNCTION(BlueprintCallable , Category = PlayerCharacter)
	uint8 GetCurrentStateMachineID() { return HFSM->GetCurrentStateMachineID(); }
	UFUNCTION(BlueprintCallable, Category = PlayerCharacter)
	uint8 GetCurrentStateID() { return HFSM->GetCurrentStateID(); }

protected:
	UFUNCTION(BlueprintCallable, Category = PlayerCharacter)
	FVector2D GetInputDirection() const { return inputDirection; }
protected:
	// To add mapping context
	virtual void BeginPlay() override;
	virtual void Look(const FInputActionValue& Value);
	virtual void Move(const FInputActionValue& Value);
	virtual void MoveCompleted(const FInputActionValue& Value);

protected:

	FVector2D inputDirection;
protected:

	UPROPERTY()
	TObjectPtr<UHFSMComponent> HFSM;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* defaultMappingContext;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FPlayerInputData inputData;
};
