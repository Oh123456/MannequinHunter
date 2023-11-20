// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "DebugLog.h"
#include "Defines.h"
#include "OJKFramework.h"


APlayerCharacter::APlayerCharacter() : Super(),
inputDirection(0.0f,0.0f) , HFSM(nullptr)
{
	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputMappingContext, inputMappingContext, TEXT("/Game/ThirdPerson/Input/IMC_Default.IMC_Default"));

	if (inputMappingContext.Succeeded())
	{
		defaultMappingContext = inputMappingContext.Object;
	}

	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputAction, findJumpAction, TEXT("/Game/ThirdPerson/Input/Actions/IA_Jump.IA_Jump"));

	if (findJumpAction.Succeeded())
	{
		inputData.jumpAction = findJumpAction.Object;
	}

	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputAction, findMoveAction, TEXT("/Game/ThirdPerson/Input/Actions/IA_Move.IA_Move"))

	if (findMoveAction.Succeeded())
	{
		inputData.moveAction = findMoveAction.Object;
	}

	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputAction, findLookAction, TEXT("/Game/ThirdPerson/Input/Actions/IA_Look.IA_Look"))

	if (findLookAction.Succeeded())
	{
		inputData.lookAction = findLookAction.Object;
	}

}



void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	inputDirection = MovementVector;
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::MoveCompleted(const FInputActionValue& Value)
{
	inputDirection = FVector2D::ZeroVector;
}


void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (combatComponent && combatComponent->IsLockOn())
		return;
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (combatComponent == nullptr)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG_WARNING(Framework, TEXT("%s has no CombatComponent!! Please check"), *UKismetSystemLibrary::GetDisplayName(this))
#endif
		return;
	}
	combatComponent->DodgeDirectionDelegate().BindLambda([this]()
		{
			if (!GetCharacterMovement()->bOrientRotationToMovement || 
				GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr))
				return this->inputDirection;
			return FVector2D(0.0f, 1.0f);
		});
}

