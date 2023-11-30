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

	//UPROPERTY(EditAnywhere)
	//TArray<FName> keyNames;

	//const FKey* inputBufferKey;

	UPROPERTY()
	const class UInputAction* action;

	bool isAddableInputBuffer = false;
};

UCLASS()
class OJKFRAMEWORK_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE(FInputBufferAction)
//protected:
//	struct FInputBufferData
//	{
//		FInputBufferAction inputBufferAction;
//		bool isAddableInputBuffer = false;
//	};
//inline void SetIsAddableInputBuffer(bool b) { inputBufferData.isAddableInputBuffer = b; }
//inline bool GetIsAddableInputBuffer() const { return inputBufferData.isAddableInputBuffer; }
//inline bool IsInputBuffer() const { return inputBufferData.inputBufferAction.IsBound(); }
//template<typename UClass>
//void AddInputBufferAction(UClass* uclass, void(UClass::*acion)());
//void ExecuteInputBuffer();
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

//template<typename UClass>
//inline void AActionPlayerController::AddInputBufferAction(UClass* uclass, void(UClass::*acion)())
//{
//	if (IsInputBuffer())
//		return;
//	inputBufferData.inputBufferAction.BindUObject(uclass, acion);
//}
