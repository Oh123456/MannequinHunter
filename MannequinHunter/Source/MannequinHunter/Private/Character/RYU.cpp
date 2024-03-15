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


void ARYU::SetInputAction()
{
	
	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputAction, findCombatAction, TEXT("/Game/BP/Input/IA_Combat.IA_Combat"));

	if (findCombatAction.Succeeded())
	{
		inputData.combatAction = findCombatAction.Object;
	}

	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputAction, findDodgeAction, TEXT("/Game/BP/Input/IA_Dodge.IA_Dodge"))

	if (findDodgeAction.Succeeded())
	{
		inputData.dodgeAction = findDodgeAction.Object;
	}

	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputAction, findLAttackAction, TEXT("/Game/BP/Input/IA_LAttack.IA_LAttack"))

	if (findLAttackAction.Succeeded())
	{
		inputData.AttackAction = findLAttackAction.Object;
	}

	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputAction, findRAttackAction, TEXT("/Game/BP/Input/IA_RAttack.IA_RAttack"))

	if (findRAttackAction.Succeeded())
	{
		inputData.Attack2Action = findRAttackAction.Object;
	}

	CONSTRUCTOR_HELPERS_FOBJECTFINDER(UInputAction, findLockOnAction, TEXT("/Game/BP/Input/IA_LockOn.IA_LockOn"))

	if (findLockOnAction.Succeeded())
	{
		inputData.lockOnAction = findLockOnAction.Object;
	}
}

void ARYU::ToggleCombat()
{
	if (HFSM)
	{
		HFSM->SetStateOrder(EStateOrder::ToggleCombat | EStateOrder::Idle);
		//HFSM->CheckStateMachineCondition();
	}
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

void ARYU::Dodge(const FInputActionInstance& inputActionInstance)
{
	AddInputBuffer(inputActionInstance);
	if (HFSM)
	{
		HFSM->SetStateOrder(EStateOrder::Dodge);
	}
}

void ARYU::LAttack(const FInputActionInstance& inputActionInstance)
{
	AddInputBuffer(inputActionInstance);
	Attack(EPlayerInputType::LButton);

}

void ARYU::RAttack(const FInputActionInstance& inputActionInstance)
{
	AddInputBuffer(inputActionInstance);
	Attack(EPlayerInputType::RButton);
}

void ARYU::Attack(EPlayerInputType type)
{
	if (HFSM)
	{
		UMannequinHunterCombatComponent* mannequinHunterCombatComponent = StaticCast<UMannequinHunterCombatComponent*>(combatComponent);
		mannequinHunterCombatComponent->SetPlyerInputType(type);


		EStateOrder stateOrder = EStateOrder::Attack;
		if (HFSM->GetCurrentStateMachineID() == StaticCast<uint8>(EPlayerStateMachine::Default))
			stateOrder |= EStateOrder::ToggleCombat;
		HFSM->SetStateOrder(stateOrder);
	}
}

void ARYU::LockOn()
{
	if (combatComponent)
		combatComponent->SetLockOnTarget();
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
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(playerInputComponent)) {


		//Jumping
		enhancedInputComponent->BindAction(inputData.jumpAction, ETriggerEvent::Triggered, this, &ARYU::InputJumpKey);
		enhancedInputComponent->BindAction(inputData.jumpAction, ETriggerEvent::Completed, this, &ARYU::InputJumpKeyCompleted);

		//Moving
		enhancedInputComponent->BindAction(inputData.moveAction, ETriggerEvent::Triggered, this, &ARYU::Move);
		enhancedInputComponent->BindAction(inputData.moveAction, ETriggerEvent::Completed, this, &ARYU::MoveCompleted);

		//Looking
		enhancedInputComponent->BindAction(inputData.lookAction, ETriggerEvent::Triggered, this, &ARYU::Look);
		
		enhancedInputComponent->BindAction(inputData.combatAction, ETriggerEvent::Triggered, this, &ARYU::ToggleCombat);

		enhancedInputComponent->BindAction(inputData.dodgeAction, ETriggerEvent::Triggered, this, &ARYU::Dodge);

		enhancedInputComponent->BindAction(inputData.AttackAction, ETriggerEvent::Triggered, this, &ARYU::LAttack);
		
		enhancedInputComponent->BindAction(inputData.Attack2Action, ETriggerEvent::Triggered, this, &ARYU::RAttack);

		enhancedInputComponent->BindAction(inputData.lockOnAction, ETriggerEvent::Triggered, this, &ARYU::LockOn);

	}
}

void ARYU::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	// юс╫ц
	AFistWeapon* weapon = (combatComponent->CreateEquipment<AFistWeapon>(weaponClass, ECombatEquipmentSlot::E_MainWeapon));

	weapon->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
	weapon->SetWeaponOwner(this);

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

	const FMannequinHunterStatusDataTable* rowTableData = GetGameInstance()->GetSubsystem<UTableSubsystem>()->GetTable<FMannequinHunterStatusDataTable>(TEXT("Test"));
	//const FMannequinHunterStatusDataTable* rowTableData = FTableManager::GetInstance()->GetTable<FMannequinHunterStatusDataTable>(TEXT("Test"));

	mannequinHunterCombatComponent->SetStatusData(rowTableData);

#ifdef UE_BUILD_DEBUG
	if (playerInputLog == nullptr)
	{
		playerInputLog = MakeShared<FPlayerInputLog>();
	}
#endif
}
