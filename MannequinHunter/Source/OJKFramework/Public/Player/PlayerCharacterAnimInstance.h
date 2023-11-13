// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionCharacterAnimInstance.h"
#include "PlayerCharacter.h"
#include "PlayerCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OJKFRAMEWORK_API UPlayerCharacterAnimInstance : public UActionCharacterAnimInstance
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintPure, Category = PlayerCharacterAnimInstance, meta = (BlueprintThreadSafe))
	inline uint8 GetCurrentState() 
	{
		APlayerCharacter* playerCharacter = static_cast<APlayerCharacter*>(ownerCharacter);
		if (playerCharacter == nullptr)
			return 0;
		return playerCharacter->GetCurrentStateID();
	}
	UFUNCTION(BlueprintPure, Category = PlayerCharacterAnimInstance, meta = (BlueprintThreadSafe))
	inline uint8 GetCurrentStateMachineID()
	{
		APlayerCharacter* playerCharacter = static_cast<APlayerCharacter*>(ownerCharacter);
		if (playerCharacter == nullptr)
			return 0;
		return playerCharacter->GetCurrentStateMachineID();
	}
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	
};
