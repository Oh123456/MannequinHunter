// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseStaticMeshWeapon.h"
#include "Components/StaticMeshComponent.h"

ABaseStaticMeshWeapon::ABaseStaticMeshWeapon() : Super()
{
	USceneComponent* defulatRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefulatRoot"));
	RootComponent = defulatRoot;

	weaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	weaponMeshComponent->SetupAttachment(defulatRoot);
	weaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
