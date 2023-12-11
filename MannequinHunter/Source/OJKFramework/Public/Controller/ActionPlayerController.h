// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FInputBufferInfo
{
	GENERATED_BODY()

	UPROPERTY()
	const class UInputAction* action;

	bool isAddableInputBuffer = false;
};

UCLASS()
class OJKFRAMEWORK_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	inline void SetIsAddableInputBuffer(bool b) { inputBufferInfo.isAddableInputBuffer = b; }
	inline bool GetIsAddableInputBuffer() const { return inputBufferInfo.isAddableInputBuffer; }

	inline bool IsInputBuffer() const { return inputBufferInfo.action != nullptr; }

	void ExecuteInputBuffer();

	void AddInputBuffer(const struct FInputActionInstance& inputActionInstance);
private:
	//FInputBufferData inputBufferData;
	UPROPERTY(EditAnywhere)
	FInputBufferInfo inputBufferInfo;


};
