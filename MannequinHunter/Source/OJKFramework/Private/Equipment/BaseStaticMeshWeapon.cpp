// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseStaticMeshWeapon.h"
#include "Components/StaticMeshComponent.h"

ABaseStaticMeshWeapon::ABaseStaticMeshWeapon() : Super()
{
	USceneComponent* defaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = defaultRoot;

	weaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	weaponMeshComponent->SetupAttachment(defaultRoot);
	weaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
