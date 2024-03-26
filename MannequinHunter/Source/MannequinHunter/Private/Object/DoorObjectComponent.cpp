// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/DoorObjectComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
UDoorObjectComponent::UDoorObjectComponent()
{
	
}

void UDoorObjectComponent::CallMoveDoor()
{
	GetWorld()->GetTimerManager().SetTimer(doorTimerHandle, this, &UDoorObjectComponent::MoveDoor, interval, true);
}

void UDoorObjectComponent::MoveDoor()
{
	FVector newPos = UKismetMathLibrary::VInterpTo(doorObjectComponent->GetRelativeLocation(), movePos, interval, InterpSpeed);
	doorObjectComponent->SetRelativeLocation(newPos);

	if (newPos.Equals(movePos))
	{
		GetWorld()->GetTimerManager().ClearTimer(doorTimerHandle);
	}
}
