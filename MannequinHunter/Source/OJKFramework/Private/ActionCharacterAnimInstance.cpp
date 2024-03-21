// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCharacterAnimInstance.h"
#include "BaseActionCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "GameFramework/PlayerController.h"


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

void UActionCharacterAnimInstance::SetSpeed(const UCharacterMovementComponent* characterMovement)
{
	speed = FMath::Sqrt((velocity.X * velocity.X) + (velocity.Y * velocity.Y));
}

void UActionCharacterAnimInstance::SetAngle(const UCharacterMovementComponent* characterMovement)
{
	const FVector& inverseVector = UKismetMathLibrary::InverseTransformDirection(ownerCharacter->GetActorTransform(), velocity);
	angle = UKismetMathLibrary::MakeRotFromX(inverseVector).Yaw;


	//const UCharacterCombatComponent* characterCombat = ownerCharacter->GetCombatComponent();

	//const FTransform* transform = nullptr;

	//if (characterCombat == nullptr)
	//{
	//	transform = &ownerCharacter->GetActorTransform();
	//}
	//else
	//{
	//	if (characterCombat->IsLockOn())
	//	{
	//		const AActor* controller = ownerCharacter->GetController();
	//		transform = &controller->GetActorTransform();
	//	}
	//	else
	//	{
	//		transform = &ownerCharacter->GetActorTransform();
	//	}
	//}

	//const FVector& inverseVector = UKismetMathLibrary::InverseTransformDirection(*transform, velocity);
	//angle = UKismetMathLibrary::MakeRotFromX(inverseVector).Yaw;
}


void UActionCharacterAnimInstance::SetBlendSpaceValue(const UCharacterMovementComponent*  characterMovement)
{
	velocity = characterMovement->Velocity;
	SetSpeed(characterMovement);
	SetAngle(characterMovement);
}