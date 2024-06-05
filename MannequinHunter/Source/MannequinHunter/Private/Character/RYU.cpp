// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RYU.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HFSM/RYUHFSMComponent.h"
#include "Animation/RYUAnimInstance.h"
#include "InputMappingContext.h"
#include "DebugLog.h"
#include "CombatSystem/CombatAnimationData.h"
#include "Character/PlayerCommonEnums.h"
#include "Controller/ActionPlayerController.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Utility/PlayerInputLog.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/MannequinHunterStatusTable.h"
#include "Equipment/FistWeapon.h"
#include "CombatSystem/CharacterCombatComponent.inl"

ARYU::ARYU() : Super()
{
	SetInputAction();
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

	combatComponent = CreateDefaultSubobject<UMannequinHunterCombatComponent>(TEXT("PlayerCombatSystem"));

	HFSM = CreateDefaultSubobject<URYUHFSMComponent>(TEXT("RYUHFSM"));


}

void ARYU::InputJumpKey()
{
	URYUAnimInstance* ryuAnimInstance = StaticCast<URYUAnimInstance*>(GetMesh()->GetAnimInstance());
	ryuAnimInstance->SetIsInputJumpKey(true);
}

void ARYU::InputJumpKeyCompleted()
{
	URYUAnimInstance* ryuAnimInstance = StaticCast<URYUAnimInstance*>(GetMesh()->GetAnimInstance());
	ryuAnimInstance->SetIsInputJumpKey(false);
	Super::StopJumping();
}


void ARYU::TestWeaponTypeChange(EWeaponType type)
{
	UMannequinHunterCombatComponent* mannequinHunterCombatComponent = StaticCast<UMannequinHunterCombatComponent*>(combatComponent);
	mannequinHunterCombatComponent->SetWeaponType(type);
}


void ARYU::Falling()
{
	if (HFSM)
	{
		HFSM->SetStateOrder(EStateOrder::Jump | EStateOrder::Falling);
	}
}

void ARYU::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	// Set up action bindings
	Super::SetupPlayerInputComponent(playerInputComponent);
}

void ARYU::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// юс╫ц
	AFistWeapon* weapon = (combatComponent->CreateEquipment<AFistWeapon>(weaponClass, ECombatEquipmentSlot::E_MainWeapon));
	
	if (weapon)
	{
		weapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		weapon->SetWeaponOwner(this);
	}

	UMannequinHunterCombatComponent* mannequinHunterCombatComponent = StaticCast<UMannequinHunterCombatComponent*>(combatComponent);
	mannequinHunterCombatComponent->SetWeaponType(EWeaponType::Fist);
	mannequinHunterCombatComponent->SetCombatAnimationData(EWeaponType::Fist);



	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(defaultMappingContext, 0);
		}
	}

	const FMannequinHunterStatusDataTable* rowTableData = GetGameInstance()->GetSubsystem<UTableSubsystem>()->GetTable<FMannequinHunterStatusDataTable>(TEXT("RYU"));

	mannequinHunterCombatComponent->SetStatusData(rowTableData);

#ifdef UE_BUILD_DEBUG
	if (playerInputLog == nullptr)
	{
		playerInputLog = MakeShared<FPlayerInputLog>();
	}
#endif
}
