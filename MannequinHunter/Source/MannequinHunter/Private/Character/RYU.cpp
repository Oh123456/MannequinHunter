// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RYU.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CombatSystem/PlayerCharacterCombatComponent.h"
#include "HFSM/RYUHFSMComponent.h"
#include "InputMappingContext.h"
#include "DebugLog.h"

ARYU::ARYU() : Super()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	combatComponent = CreateDefaultSubobject<UPlayerCharacterCombatComponent>(TEXT("PlayerCombatSystem"));

	HFSM = CreateDefaultSubobject<URYUHFSMComponent>(TEXT("RYUHFSM"));
	weaponType = ERYUWeaponType::Fist;
}

void ARYU::Move(const FInputActionValue& value)
{
	APlayerCharacter::Move(value);
}

void ARYU::Look(const FInputActionValue& value)
{
	APlayerCharacter::Look(value);
}

void ARYU::ToggleCombat()
{
	if (HFSM)
	{
		HFSM->CheckStateMachineCondition();
	}
}


void ARYU::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(playerInputComponent)) {


		//Jumping
		enhancedInputComponent->BindAction(inputData.jumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		enhancedInputComponent->BindAction(inputData.jumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		enhancedInputComponent->BindAction(inputData.moveAction, ETriggerEvent::Triggered, this, &ARYU::Move);
		enhancedInputComponent->BindAction(inputData.moveAction, ETriggerEvent::Completed, this, &ARYU::MoveCompleted);

		//Looking
		enhancedInputComponent->BindAction(inputData.lookAction, ETriggerEvent::Triggered, this, &ARYU::Look);
		
		enhancedInputComponent->BindAction(inputData.combatAction, ETriggerEvent::Triggered, this, &ARYU::ToggleCombat);

	}
}

void ARYU::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(defaultMappingContext, 0);
		}
	}
}
