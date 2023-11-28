// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"


/**
 * 
 */



UCLASS()
class OJKFRAMEWORK_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE(FInputBufferAction)
public:
	inline void SetIsAddableInputBuffer(bool b) { isAddableInputBuffer = b; }
	inline bool GetIsAddableInputBuffer() const { return isAddableInputBuffer; }

	inline bool IsInputBuffer() const { return inputBufferAction.IsBound(); }

	template<typename UClass>
	void AddInputBufferAction(UClass* uclass, void(UClass::*acion)());

	void ExecuteInputBuffer();
private:
	FInputBufferAction inputBufferAction;
	bool isAddableInputBuffer = false;
};

template<typename UClass>
inline void AActionPlayerController::AddInputBufferAction(UClass* uclass, void(UClass::*acion)())
{
	if (IsInputBuffer())
		return;
	inputBufferAction.BindUObject(uclass, acion);
}
