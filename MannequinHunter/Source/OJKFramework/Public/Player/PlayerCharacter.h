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
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FPlayerInputData
{
	GENERATED_BODY()
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> jumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> moveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> lookAction;

	/** PlayerCombat NotCombat Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> combatAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> dodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> Attack2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> inputBufferInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> lockOnAction;
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


	//const UInputMappingContext* GetMappingContext() { return defaultMappingContext; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return followCamera; }

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
	virtual void AddInputBuffer(const struct FInputActionInstance& inputActionInstance);
protected:

	FVector2D inputDirection;
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* cameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* followCamera;
protected:

	UPROPERTY()
	TObjectPtr<UHFSMComponent> HFSM;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* defaultMappingContext;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FPlayerInputData inputData;

	UPROPERTY()
	TObjectPtr<class AActionPlayerController> actionPlayerController;
};
