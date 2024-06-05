// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/PlayerCharacterCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/PlayerCharacter.h"


UPlayerCharacterCombatComponent::UPlayerCharacterCombatComponent() : Super(),
LockOnLength(1000.f)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCharacterCombatComponent::RecoverStamina()
{
	status.AddStamina(CalculateRecoveryStamina());

	if (status.CheckMaxStamina())
	{
		GetWorld()->GetTimerManager().ClearTimer(staminaTimerHandle);
	}
	
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

	FVector ownerLocation = owner->GetActorLocation();

	TArray<FHitResult> hitResults;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		ownerLocation, ownerLocation,
		LockOnLength,
		lockOnTargetObjectType, false ,
		TArray<AActor*>(), EDrawDebugTrace::ForDuration, hitResults, true);

	AActor* targetActor = nullptr;
	bool bOrientRotationToMovement = false;
	if (isHit)
	{
		float minLength = 0.0f;
		float length = 0.0f;
		int32 size = hitResults.Num();
		FHitResult& hitResult = hitResults[0];
		AActor* hitActor = hitResult.GetActor();
		targetActor = hitActor;
		minLength = FVector::DistSquared(hitActor->GetActorLocation(), ownerLocation);
		for (int32 i = 1; i < size; i++)
		{
			hitResult = hitResults[i];
			hitActor = hitResult.GetActor();

			length = FVector::DistSquared(hitActor->GetActorLocation(), ownerLocation);
			if (minLength > length)
			{
				minLength = length;
				targetActor = hitResult.GetActor();
			}

		}
	}

 	//targetActor = hitActor;
	SetTargetActor(targetActor);
	//owner->GetCharacterMovement()->bOrientRotationToMovement = bOrientRotationToMovement;
	owner->bUseControllerRotationYaw = !bOrientRotationToMovement;
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

	status.OnChangeStaminaStatus.AddLambda([this](const TSharedPtr<FStatusData>& statusData)
	{
		if (statusData->maxStamina > statusData->stamina)
		{
			GetWorld()->GetTimerManager().SetTimer(staminaTimerHandle, this, &UPlayerCharacterCombatComponent::RecoverStamina, recoveryStaminaTime, true);
		}
	});
}

int32 UPlayerCharacterCombatComponent::CalculateRecoveryStamina()
{
	return recoveryStamina * recoveryStaminaTime;
}

void UPlayerCharacterCombatComponent::Death(const FDeathInfo& deathInfo)
{
	Super::Death(deathInfo);
	
	characterCombatData.owner->DisableInput(Cast<APlayerController>(characterCombatData.owner->GetController()));
}
