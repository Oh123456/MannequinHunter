// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/ActionPlayerController.h"
#include "Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "DebugLog.h"

void AActionPlayerController::AddInputBuffer(const FInputActionInstance& inputActionInstance)
{
	if (!inputBufferInfo.isAddableInputBuffer /*|| inputBufferInfo.action*/)
		return;

	inputBufferInfo.action = inputActionInstance.GetSourceAction();

}

void AActionPlayerController::ExecuteInputBuffer()
{
	if (inputBufferInfo.action == nullptr)
		return;

	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(GetPawn());

	FString actionName = inputBufferInfo.action->GetName();

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(GetPawn()->InputComponent);

	if (enhancedInputComponent)
	{


		const TArray<TUniquePtr<FEnhancedInputActionEventBinding>>& bindings = enhancedInputComponent->GetActionEventBindings();
		const TUniquePtr<FEnhancedInputActionEventBinding>* eventBinding = bindings.FindByPredicate(
			[&actionName](const TUniquePtr<FEnhancedInputActionEventBinding>& data)
			{
				return data->GetAction()->GetName().Equals(actionName);
			});


		if (eventBinding)
		{
			(*eventBinding)->Execute(FInputActionInstance(inputBufferInfo.action));
		}

		inputBufferInfo.action = nullptr;
	}

}