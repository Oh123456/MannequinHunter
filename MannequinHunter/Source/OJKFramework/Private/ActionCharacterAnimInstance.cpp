// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCharacterAnimInstance.h"
#include "BaseActionCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"


void UActionCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	ownerCharacter = Cast<ABaseActionCharacter>(TryGetPawnOwner());
}

void UActionCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (ownerCharacter == nullptr)
		return;

	UCharacterMovementComponent* characterMovement = ownerCharacter->GetCharacterMovement();

	if (characterMovement)
	{

		SetBlendSpaceValue(characterMovement);

		isFalling = characterMovement->IsFalling();
	}
}


void UActionCharacterAnimInstance::SetBlendSpaceValue(const UCharacterMovementComponent*  characterMovement)
{
	velocity = characterMovement->Velocity;
	speed =  FMath::Sqrt((velocity.X * velocity.X) + (velocity.Y * velocity.Y));

	const FVector& inverseVector = UKismetMathLibrary::InverseTransformDirection(ownerCharacter->GetActorTransform(), velocity);
	angle = UKismetMathLibrary::MakeRotFromX(inverseVector).Yaw;
}