// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/PlayerCharacterCombatComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UPlayerCharacterCombatComponent::UPlayerCharacterCombatComponent() : Super(),
LockOnLength(1000.f)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCharacterCombatComponent::SetLockOnTarget()
{
	ACharacter* owner = characterCombatData.owner;
	if (IsLockOn())
	{
		Super::SetLockOnTarget();
		owner->GetCharacterMovement()->bOrientRotationToMovement = true;
		return;
	}

	UCameraComponent* cameraComponent = findCameraComponentDelegate.Execute();



	FVector ownerLocation = owner->GetActorLocation();

	const AActor* targetActor = GetTargetActor();

	FHitResult hitResult;
	
	bool isHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		this,
		ownerLocation, ownerLocation,
		LockOnLength,
		lockOnTargetObjectType, false ,
		TArray<AActor*>(), EDrawDebugTrace::ForDuration, hitResult, true);

	AActor* hitActor = nullptr;
	bool bOrientRotationToMovement = true;
	if (isHit)
	{
		hitActor = hitResult.GetActor();
		if (hitActor->GetComponentByClass<UCombatComponent>())
		{
			if (targetActor == nullptr)
				bOrientRotationToMovement = false;
			else
				hitActor = nullptr;
			
		}
	}

 	//targetActor = hitActor;
	SetTargetActor(hitActor);
	owner->GetCharacterMovement()->bOrientRotationToMovement = bOrientRotationToMovement;
	//owner->bUseControllerRotationYaw = !bOrientRotationToMovement;
}

void UPlayerCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	findCameraComponentDelegate.BindLambda([this]() -> 
		UCameraComponent* 
		{
			return characterCombatData.owner->GetComponentByClass<UCameraComponent>();
		});

	lockOnTargetIgnoreActor.Add(characterCombatData.owner);

	TArray<TEnumAsByte<EObjectTypeQuery>> objectType;
	lockOnTargetObjectType.Add(static_cast<EObjectTypeQuery>(ECollisionChannel::ECC_Pawn));
}
