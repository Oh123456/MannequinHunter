// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MannequinHunterPlayerCharacter.h"
#include "Character/PlayerCommonEnums.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/MannequinHunterGameMode.h"
#include "Controller/ActionPlayerController.h"

void AMannequinHunterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(playerInputComponent))
	{


		//Jumping
		enhancedInputComponent->BindAction(inputData.jumpAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::InputJumpKey);
		enhancedInputComponent->BindAction(inputData.jumpAction, ETriggerEvent::Completed, this, &AMannequinHunterPlayerCharacter::InputJumpKeyCompleted);

		//Moving
		enhancedInputComponent->BindAction(inputData.moveAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::Move);
		enhancedInputComponent->BindAction(inputData.moveAction, ETriggerEvent::Completed, this, &AMannequinHunterPlayerCharacter::MoveCompleted);

		//Looking
		enhancedInputComponent->BindAction(inputData.lookAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::Look);

		enhancedInputComponent->BindAction(inputData.combatAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::ToggleCombat);

		enhancedInputComponent->BindAction(inputData.dodgeAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::Dodge);

		enhancedInputComponent->BindAction(inputData.AttackAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::LAttack);

		enhancedInputComponent->BindAction(inputData.Attack2Action, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::RAttack);

		enhancedInputComponent->BindAction(inputData.lockOnAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::LockOn);

		enhancedInputComponent->BindAction(inputData.InventoryAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::OnInventory);

		enhancedInputComponent->BindAction(inputData.infoAction, ETriggerEvent::Triggered, this, &AMannequinHunterPlayerCharacter::OnInfo);
	}

}



void AMannequinHunterPlayerCharacter::SetInputAction()
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

void AMannequinHunterPlayerCharacter::ToggleCombat()
{
	if (HFSM)
	{
		HFSM->SetStateOrder(EStateOrder::ToggleCombat | EStateOrder::Idle);
	}
}

void AMannequinHunterPlayerCharacter::InputJumpKey()
{
}

void AMannequinHunterPlayerCharacter::InputJumpKeyCompleted()
{
}

void AMannequinHunterPlayerCharacter::Dodge(const FInputActionInstance& inputActionInstance)
{
	AddInputBuffer(inputActionInstance);
	if (HFSM)
	{
		HFSM->SetStateOrder(EStateOrder::Dodge);
	}
}


void AMannequinHunterPlayerCharacter::LAttack(const FInputActionInstance& inputActionInstance)
{
	if (actionPlayerController->bShowMouseCursor)
		return;
	AddInputBuffer(inputActionInstance);
	Attack(EPlayerInputType::LButton);

}

void AMannequinHunterPlayerCharacter::RAttack(const FInputActionInstance& inputActionInstance)
{
	if (actionPlayerController->bShowMouseCursor)
		return;
	AddInputBuffer(inputActionInstance);
	Attack(EPlayerInputType::RButton);
}

void AMannequinHunterPlayerCharacter::Attack(EPlayerInputType type)
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

void AMannequinHunterPlayerCharacter::LockOn()
{
	if (combatComponent)
		combatComponent->SetLockOnTarget();
}

void AMannequinHunterPlayerCharacter::OnInventory()
{
	AMannequinHunterGameMode* gameMode = Cast<AMannequinHunterGameMode>(UGameplayStatics::GetGameMode(this));
	if (gameMode == nullptr)
		return;
	gameMode->ToggleInventory();
	
}

void AMannequinHunterPlayerCharacter::OnInfo()
{
	AMannequinHunterGameMode* gameMode = Cast<AMannequinHunterGameMode>(UGameplayStatics::GetGameMode(this));
	if (gameMode == nullptr)
		return;
	gameMode->ToggleInfo();
}


void AMannequinHunterPlayerCharacter::Look(const FInputActionValue & Value)
{
	if (actionPlayerController->bShowMouseCursor)
		return;
	Super::Look(Value);
}