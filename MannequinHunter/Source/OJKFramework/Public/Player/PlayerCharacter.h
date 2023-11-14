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
};

UCLASS()
class OJKFRAMEWORK_API APlayerCharacter : public ABaseActionCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UHFSMComponent* GetHFSM() { return HFSM; }

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

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* defaultMappingContext;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FPlayerInputData inputData;
};
