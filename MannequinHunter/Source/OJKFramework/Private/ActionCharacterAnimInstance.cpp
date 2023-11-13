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

	SetBlendSpaceValue();

}


void UActionCharacterAnimInstance::SetBlendSpaceValue()
{
	UCharacterMovementComponent* characterMovemnet = ownerCharacter->GetCharacterMovement();

	const FVector& velocity = characterMovemnet->Velocity;
	speed =  FMath::Sqrt((velocity.X * velocity.X) + (velocity.Y * velocity.Y));

	const FVector& inverseVector = UKismetMathLibrary::InverseTransformDirection(ownerCharacter->GetActorTransform(), velocity);
	angle = UKismetMathLibrary::MakeRotFromX(inverseVector).Yaw;
}