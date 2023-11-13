// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseSkeletalMeshWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ABaseSkeletalMeshWeapon::ABaseSkeletalMeshWeapon() : Super()
{
	USceneComponent* defulatRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefulatRoot"));
	RootComponent = defulatRoot;

	weaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	weaponMeshComponent->SetupAttachment(defulatRoot);
	weaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
