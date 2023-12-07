// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/HitBoxActor.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AHitBoxActor::AHitBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	hitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	hitBox->InitCapsuleSize(35.0f, 35.0f);
}

void AHitBoxActor::SetCylinderActive(bool isActive)
{
	if(isActive)
		hitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
		hitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

