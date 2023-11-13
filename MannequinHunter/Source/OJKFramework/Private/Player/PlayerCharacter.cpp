// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

APlayerCharacter::APlayerCharacter() : Super(),
inputDirection(0.0f,0.0f) , HFSM(nullptr)
{
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


void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (combatComponent->IsLockOn())
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


	combatComponent->DodgeDirectionDelegate().BindLambda([this]()
		{
			if (!GetCharacterMovement()->bOrientRotationToMovement || 
				GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr))
				return this->inputDirection;
			return FVector2D(0.0f, 1.0f);
		});
}

