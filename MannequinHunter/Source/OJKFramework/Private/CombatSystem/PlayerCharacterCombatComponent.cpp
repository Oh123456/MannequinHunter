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
		//owner->GetCharacterMovement()->bOrientRotationToMovement = true;
		return;
	}

	UCameraComponent* cameraComponent = findCameraComponentDelegate.Execute();



	FVector ownerLocation = owner->GetActorLocation();

	const AActor* targetActor = GetTargetActor();


	TArray<FHitResult> hitResults;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		ownerLocation, ownerLocation,
		LockOnLength,
		lockOnTargetObjectType, false ,
		TArray<AActor*>(), EDrawDebugTrace::ForDuration, hitResults, true);

	AActor* hitActor = nullptr;
	bool bOrientRotationToMovement = false;
	if (isHit)
	{
		float minLength = 0.0f;
		float length = 0.0f;
		int32 size = hitResults.Num();
		FHitResult& hitResult = hitResults[0];
		hitActor = hitResult.GetActor();
		minLength = FVector::DistSquared(hitActor->GetActorLocation(), ownerLocation);
		for (int32 i = 1 ; i < size; i++)
		{
			hitResult = hitResults[i];
			if (hitActor->GetComponentByClass<UCombatComponent>())
			{
				length = FVector::DistSquared(hitActor->GetActorLocation(), ownerLocation);
				if (minLength > length)
				{
					minLength = length;
					hitActor = hitResult.GetActor();
				}
			}
		}
	}

 	//targetActor = hitActor;
	SetTargetActor(hitActor);
	//owner->GetCharacterMovement()->bOrientRotationToMovement = bOrientRotationToMovement;
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
