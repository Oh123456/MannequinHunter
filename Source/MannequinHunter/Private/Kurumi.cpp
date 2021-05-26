// Fill out your copyright notice in the Description page of Project Settings.

#include "Kurumi.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

#include "FindHelper.h"

AKurumi::AKurumi()
{
	// 컨트롤러로 회전
	bUseControllerRotationYaw = false;

	USkeletalMesh* skeletalMesh;
	FindHelper::AssetsFindObejct(&skeletalMesh, TEXT("SkeletalMesh'/Game/PinkGirl/Character/Meshes/SK_Kurumi.SK_Kurumi'"));
	GetMesh()->SetSkeletalMesh(skeletalMesh);


	UPrimitiveComponent* primiveComponest = GetCapsuleComponent();
	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("Custom"));
	// 카메라는 무시
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);


	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FolliwCamera"));
	followCamera->SetupAttachment(cameraBoom);
	followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	weapone = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapone"));
	weapone->SetupAttachment(GetMesh(), FName(TEXT("__sheath_socket")));

	sheath = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sheath"));
	sheath->SetupAttachment(GetMesh(), FName(TEXT("cc_SwordSocket")));


	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->RotationRate.Yaw = 720.0f;




}

void AKurumi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &AKurumi::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKurumi::MoveRight);
}

void AKurumi::MoveForward(float Value)
{
	FRotator rotetaion(0.0f, GetControlRotation().Yaw, 0.0f);
	// get forward vector
	const FVector Direction = FRotationMatrix(rotetaion).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, Value);
}

void AKurumi::MoveRight(float Value)
{

	FRotator rotetaion(0.0f, GetControlRotation().Yaw, 0.0f);
	// get forward vector
	const FVector Direction = FRotationMatrix(rotetaion).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, Value);
}
