// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/HitBoxActor.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AHitBoxActor::AHitBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	defaultComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(defaultComponent);

	hitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	hitBox->InitCapsuleSize(20.0f, 20.0f);
	hitBox->SetupAttachment(defaultComponent);
}

void AHitBoxActor::SetCylinderActive(bool isActive)
{
	if(isActive)
		hitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
		hitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

