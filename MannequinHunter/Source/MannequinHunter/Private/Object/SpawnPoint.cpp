// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SpawnPoint.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ArrowComponent.h"
#include "Engine/Texture2D.h"
#include "Components/CapsuleComponent.h"
#include "Components/BillboardComponent.h"

ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	capsuleComponent->ShapeColor = FColor(255, 138, 5, 255);
	capsuleComponent->bDrawOnlyIfSelected = true;
	capsuleComponent->InitCapsuleSize(40.0f, 92.0f);
	capsuleComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	capsuleComponent->bShouldCollideWhenPlacing = true;
	capsuleComponent->SetShouldUpdatePhysicsVolume(false);
	capsuleComponent->Mobility = EComponentMobility::Static;
	SetRootComponent(capsuleComponent);


#if WITH_EDITORONLY_DATA
	ConstructorHelpers::FObjectFinderOptional<UTexture2D> PlayerStartTextureObject(TEXT("/Engine/EditorResources/Spawn_Point"));


	bCollideWhenPlacing = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	arrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	arrowComponent->ArrowSize = 1.0f;
	arrowComponent->bTreatAsASprite = true;
	arrowComponent->SpriteInfo.Category = TEXT("Navigation");
	arrowComponent->SpriteInfo.DisplayName = NSLOCTEXT("SpriteCategory", "Navigation", "Navigation");
	arrowComponent->SetupAttachment(capsuleComponent);
	arrowComponent->bIsScreenSizeScaled = true;

	sprite = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
	sprite->Sprite = PlayerStartTextureObject.Get();
	sprite->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	sprite->SpriteInfo.Category = TEXT("Spawn");
	sprite->SpriteInfo.DisplayName = NSLOCTEXT("SpriteCategory", "SpawnPoint", "Spawn Point");
	sprite->bIsScreenSizeScaled = true;

	sprite->SetupAttachment(capsuleComponent);

	bIsSpatiallyLoaded = false;
#endif
}

